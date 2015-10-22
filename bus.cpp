#include "bus.h"

Bus::Bus() :
	node_msg_id(0),
	num_elem_in_queue_(0),
	my_node_id_("-1"),
	context(nullptr),
	receiver(nullptr),
	mutex_queue_(),
	cond_exist_elem_queue_() {

	msg_id_to_callback().clear();
	senders_.clear();
	for (int i = 0; i < QUEUE_LEVEL; ++i) {
		while (true == PQ_[i].empty()) {
			 
			PQ_[i].pop();
		}
	}
	while (true == recvQueue.empty()) {
		recvQueue.pop();
	}
}

Bus::~Bus() {
	for (auto& it : senders_) zmq_close(it.second);
	zmq_close(receiver_);
	zmq_ctx_destroy(context_);
}

void Bus::Init(const NodeInfo &node_info) {
	my_node_id_ = node_info.id;

	context_ = zmq_ctx_new();
	CHECK(context_ != NULL) << "[Bus::Init] create 0mq context failed";

	// one need to "sudo ulimit -n 65536" or edit /etc/security/limits.conf
	zmq_ctx_set(context_, ZMQ_MAX_SOCKETS, 65536);
	// zmq_ctx_set(context_, ZMQ_IO_THREADS, 4);

	receiver_ = zmq_socket(context_, ZMQ_ROUTER);
	CHECK(receiver_ != NULL)
	        << "[Bus::Init] create receiver socket failed: " << zmq_strerror(errno);

	std::string addr = "tcp://*:";
	addr += std::to_string(node_info.port);
	CHECK(zmq_bind(receiver_, addr.c_str()) == 0)
	        << "[Bus::Init] bind to " << addr << " failed: " << zmq_strerror(errno);

	VLOG(1) << "BIND address " << addr;
}

void Bus::Disconnect(const NodeInfo& node_info) {
	uint32_t id = node_info.id;
	if (senders_.find(id) != senders_.end()) {
		zmq_close (senders_[id]);
	}
	senders_.erase(id);
	VLOG(1) << "[Bus::Disconnect] DISCONNECT from " << node_info.id;
}

bool Bus::Connect(const NodeInfo& node_info) {
	uint32_t id = node_info.id;
	if (id == my_node_id_) {
		// it's unnecessary
		return true;
	}
	if (senders_.find(id) != senders_.end()) {
		return true;
	}
	void *sender = zmq_socket(context_, ZMQ_DEALER);
	CHECK(sender != NULL) << zmq_strerror(errno);
	uint32_t my_id = my_node_id_; // address(my_node_);

	zmq_setsockopt (sender, ZMQ_IDENTITY, my_id.data(), my_id.size());

	// uint64_t hwm = 5000000;
	// zmq_setsockopt (sender, ZMQ_SNDHWM, &hwm, sizeof(hwm));

	// connect
	std::string addr = "tcp://" + node_info.ip + ":" + std::to_string(node_info.port);
	if (zmq_connect(sender, addr.c_str()) != 0) {
		LOG(WARNING) << "[Bus::Connect] connect to " +
		             addr + " failed: " + zmq_strerror(errno);
		return false;
	}

	senders_[id] = sender;

	VLOG(1) << "Bus::Connect CONNECT to " << id << " [" << addr << "]";
	return true;
}

bool Bus::Send(SPMsg msg, std::function<int(SPMsg)> callback_function) {
	return Send(msg, (QUEUE_LEVEL - 1) / 2, callback_function);
}

bool Bus::Send(SPMsg msg, int priority, std::function<int(SPMsg)> callback_function) {
	// find the socket
	uint32_t to_id = msg->msg_header.to_id();
	auto it = senders_.find(to_id);
	if (it == senders_.end()) {
		LOG(WARNING) << "[Bus::Send] there is no socket to node " + to_id;
		return false;
	}
	msg->msg_header.set_msg_id(node_msg_id);
	msg_id_to_callback[node_msg_id++] = callback_function;

	//just put into queue
	//may need a lock
	auto lock = boost::make_unique_lock(mutex_queue_);

	PQ_[priority].push(msg);
	++num_elem_in_queue_;

	lock.unlock();

	//just one element, need to notify the recv thread
	if (num_elem_in_queue_ == 1) {
		cond_exist_elem_queue_.notify_one();
	}
	return true;
}

void Bus::Run() {
	sendThread = new std::thread(&Bus::SendThread, this);
	recvThread = new std::thread(&Bus::RecvThread, this);
	sendThread->detach();
	recvThread->detach();
}

void Bus::SendThread() {
	while (true) {
		auto lock = make_unique_lock(mutex_queue_);
		for (; num_elem_in_queue_ == 0;) {
			cond_exist_elem_queue_.wait(lock);
		}
		SPMsg msg;
		for (uint32_t i = 0; i < QUEUE_LEVEL; ++i) {
			if (PQ_[i].size() == 0) {
				continue;
			}
			msg = PQ_[i].front();
			PQ_[i].pop();
			break;
		}
		--num_elem_in_queue_;
		lock.unlock();

		LOG(INFO) << "[Bus::SendThread] sendThread get a job.";

		uint32_t to_id = msg->msg_header.to_id();
		auto it = senders_.find(to_id);

        if (it == senders_.end()) {
            LOG(WARNING) << "[Bus::SendThread] Can't find to node id " + to_id;
            return;
        }

		LOG(INFO) << "[Bus::SendThread] the to_id is " << to_id;

		void *socket = it->second;

		int tag = ZMQ_SNDMORE;

		// maybe the msg is a request which is used to get something instead of sending raw data
        if (msg->dataList.size() == 0) {
            tag = ZMQ_DONTWAIT;
        }

		int header_size = msg->msg_header.ByteSize();
		char* header_buf = new char[header_size + 5];
		CHECK(msg->msg_header.SerializeToArray(header_buf, header_size))
		    << "[Bus::SendThread] failed to serialize " 
            << msg->msg_header.ShortDebugString();

		zmq_msg_t header_msg;
		zmq_msg_init_data(&header_msg, header_buf, header_size, FreeData, NULL);

		while (true) {
			if (zmq_msg_send(&header_msg, socket, tag) == header_size) break;
			if (errno == EINTR) continue;  // may be interupted by profiler
			LOG(WARNING) << "[Bus::SendThread] failed to send task message to node [" 
                         << id
			             << "] errno: " << zmq_strerror(errno);
			return;
		}

		LOG(INFO) << "[Bus::SendThread] have sent msg_header.";

		// send the part of std::list<std::unique_ptr<char> > dataList
		{
			auto it = dataSliceList.begin();
			for (int i = 0; i < msg->dataSliceList.size() - 1; ++i) {
				tag = ZMQ_SNDMORE;
				zmq_msg_t data_msg;
				zmq_msg_init_data(&data_msg, (*it).first, (*it).second, nonFreeData, NULL);
				while (true) {
					if (zmq_msg_send(&data_msg, socket, tag) == (*it).second) break;
					if (errno == EINTR) continue;  // may be interupted by profiler
					LOG(WARNING) 
                        << "[Bus::SendThread] failed to send data message to node ["
                        << id << "] errno: " << zmq_strerror(errno);
					return;
				}
				++it;
			}
			tag = ZMQ_DONTWAIT;
			zmq_msg_t data_msg;
			zmq_msg_init_data(&data_msg, (*it).first, (*it).second, nonFreeData, NULL);
			while (true) {
				if (zmq_msg_send(&data_msg, socket, tag) == (*it).second) break;
				if (errno == EINTR) continue;  // may be interupted by profiler
				LOG(WARNING) << "[Bus::SendThread] failed to send data message to node ["
				             << id << "] errno: " << zmq_strerror(errno);
				return;
			}
		}
		LOG(INFO) << "[Bus::SendThread] have sent data.";
	}
}

void Bus::RecvThread() {
	while (true) {
		PSMsg pMsg(new Message());
		pMsg->recever = my_node_id_;

		for (int i = 0; ; ++i) {
			zmq_msg_t *zmsg = new zmq_msg_t;
			CHECK(zmq_msg_init(zmsg) == 0) << zmq_strerror(errno);
			while (true) {
				if (zmq_msg_recv(zmsg, receiver_, 0) != -1) break;
				if (errno == EINTR) continue;  // may be interupted by google profiler
				LOG(WARNING)
				        << "[Bus::RecvThread] failed to receive message. errno: "
				        << zmq_strerror(errno);
				return;
			}
			char* buf = CHECK_NOTNULL((char *)zmq_msg_data(zmsg));
			size_t size = zmq_msg_size(zmsg);

			//the first package is the identifier
			if (i == 0) {
				pMsg->sender = std::string(buf, size);
				LOG[INFO] << "[Bus::RecvThread] Get a message from" << pMsg->sender;

			} else if (i == 1) { //the second package is the Message
				CHECK(pMsg->task.ParseFromArray(buf, size))
				        << "[Bus::RecvThread] failed to parse string from "
				        << pMsg->sender
				        << ". this is " << my_node_id_ << " " << size;
				LOG(INFO)
				        << "[Bus::RecvThread] Task id = " << pMsg->task.id()
				        << ", ip = " << pMsg->task.ip()
				        << ", port = " << pMsg->task.port();
			} else if (i == 2) { //the third package is the data
				pMsg->data = new char[size];
				memcpy(pMsg->data, buf, size);
				pMsg->data_size = size;
			}
			if (!zmq_msg_more(zmsg)) { CHECK_GT(i, 0); break; }
			zmq_msg_close(zmsg);
			delete zmsg;
		}
		recvQueue.push(pMsg);
		//send a singal to tracker

	}
}
