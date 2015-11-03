#include "bus.h"

void Bus::init(const NodeInfo &node_info) {
    my_node_id = node_info.node_id;
    
    senders.clear();
    num_elem_in_queue = 0;
    for (int i = 0; i < PRIORITY_LEVEL; ++i) {
    	while (PQ[i].empty() == false) {
    		PQ[i].pop();
    	}
    }

    context = zmq_ctx_new();
	CHECK(context != NULL) << "[Bus::Init] create 0mq context failed";

	// one need to "sudo ulimit -n 65536" or edit /etc/security/limits.conf
	zmq_ctx_set(context, ZMQ_MAX_SOCKETS, 65536);
	// zmq_ctx_set(context_, ZMQ_IO_THREADS, 4);

	receiver = zmq_socket(context, ZMQ_ROUTER);
	CHECK(receiver != NULL)
	        << "[Bus::Init] create receiver socket failed: " << zmq_strerror(errno);

	std::string addr = "tcp://*:";
	addr += std::to_string(node_info.port);
	CHECK(zmq_bind(receiver, addr.c_str()) == 0)
	        << "[Bus::Init] bind to " << addr << " failed: " << zmq_strerror(errno);
	LOG(INFO) << "BIND address " << addr;
}

bool Bus::connect(const NodeInfo& node_info) {
	NodeId id = node_info.node_id;
	if (id == my_node_id) {
		// it's unnecessary
		return true;
	}
	if (senders.find(id) != senders.end()) {
		return true;
	}
	void *the_sender = zmq_socket(context, ZMQ_DEALER);
	CHECK(the_sender != NULL) << zmq_strerror(errno);
	//uint32_t my_id = my_node_id; // address(my_node_);

	//zmq_setsockopt(the_sender, ZMQ_IDENTITY, my_id, sizeof(my_id));

	// uint64_t hwm = 5000000;

	// zmq_setsockopt (sender, ZMQ_SNDHWM, &hwm, sizeof(hwm));

	// connect
	std::string addr = "tcp://" + node_info.ip + ":" + 
		std::to_string(node_info.port);
	if (zmq_connect(the_sender, addr.c_str()) != 0) {
		LOG(WARNING) << "[Bus::Connect] connect to " +
		             addr + " failed: " + zmq_strerror(errno);
		return false;
	}
	senders[id] = the_sender;

	LOG(INFO) << "Bus::Connect CONNECT to " << id << " [" << addr << "]";
	return true;
}

bool Bus::send_msg(SPMsg msg, uint32_t priority) {
	// find the socket
	NodeId to_id = msg->msg_header.to_id();
	if (senders.find(to_id) == senders.end()) {
		LOG(WARNING) << "[Bus::Send] there is no socket to node " + to_id;
		return false;
	}

	//just put into queue
	//may need a lock
	std::unique_lock<std::mutex> lock(mutex_queue);

	PQ[priority].push(msg);
	//just one element, need to notify the send thread
	if (++num_elem_in_queue == 1) {
		lock.unlock();
		cond_exist_elem_queue.notify_one();
	}
	else {
		lock.unlock();
	}

	return true;
}

void Bus::run() {
	send_thread_t = new std::thread(std::bind(&Bus::send_thread, this));
	recv_thread_t = new std::thread(std::bind(&Bus::recv_thread, this));
	send_thread_t->detach();
	recv_thread_t->detach();
}

void Bus::send_thread() {
	while (true) {
		std::unique_lock<std::mutex> lock(mutex_queue);
		for (; num_elem_in_queue == 0;) {
			cond_exist_elem_queue.wait(lock);
		}
		SPMsg msg;
		for (uint32_t i = 0; i < PRIORITY_LEVEL; ++i) {
			if (PQ[i].size() == 0) {
				continue;
			}
			msg = PQ[i].front();
			PQ[i].pop();
			break;
		}
		--num_elem_in_queue;
		lock.unlock();

		LOG(INFO) << "[Bus::send_thread] sendThread get a job.";

		NodeId to_id = msg->msg_header.to_id();
		auto it = senders.find(to_id);

        if (it == senders.end()) {
            LOG(ERROR) << "[Bus::send_thread] Can't find to node id " + to_id;
            return;
        }

		LOG(INFO) << "[Bus::send_thread] the to_id is " << to_id;

		void *socket = it->second;

		int tag = ZMQ_SNDMORE;

		// maybe the msg is a request which is used to get something instead of sending raw data
        if (msg->data_slice_list.size() == 0) {
            tag = ZMQ_DONTWAIT;
        }

		int header_size = msg->msg_header.ByteSize();
		char* header_buf = new char[header_size + 5];
		CHECK(msg->msg_header.SerializeToArray(header_buf, header_size))
		    << "[Bus::send_thread] failed to serialize " 
            << msg->msg_header.ShortDebugString();

		zmq_msg_t header_msg;
		zmq_msg_init_data(&header_msg, header_buf, header_size, nullptr, nullptr);

		while (true) {
			if (zmq_msg_send(&header_msg, socket, tag) == header_size) break;
			if (errno == EINTR) continue;  // may be interupted by profiler
			LOG(ERROR) << "[Bus::send_thread] failed to send task message to node";
			return;
		}

		delete [] header_buf;

		LOG(INFO) << "[Bus::send_thread] have sent msg_header.";

		// send the part of std::list<std::unique_ptr<string> > data_slice_list
		if (msg->data_slice_list.size() > 0) {
			auto it = msg->data_slice_list.begin();
			for (int i = 0; i < msg->data_slice_list.size() - 1; ++i) {
				tag = ZMQ_SNDMORE;
				zmq_msg_t data_msg;
				zmq_msg_init_data(&data_msg, (void *)((*it).c_str()), (*it).size(),
					nullptr, nullptr);
				//string to char *
				while (true) {
					if (zmq_msg_send(&data_msg, socket, tag) == (*it).size()) break;
					if (errno == EINTR) continue;  // may be interupted by profiler
					LOG(ERROR) 
                        << "[Bus::send_thread] failed to send data list to node";
					return;
				}
				++it;
			}
			tag = ZMQ_DONTWAIT;
			zmq_msg_t data_msg;
			zmq_msg_init_data(&data_msg, (void *)((*it).c_str()),
				(*it).size(), nullptr, nullptr);
			while (true) {
				if (zmq_msg_send(&data_msg, socket, tag) == (*it).size()) break;
				if (errno == EINTR) continue;  // may be interupted by profiler
				LOG(ERROR) << "[Bus::send_thread] failed to send data list to node";
				return;
			}
		}
		LOG(INFO) << "[Bus::send_thread] have sent data.";
	}
}

void Bus::recv_thread() {
	while(true) {
		SPMsg msg(new Message());
		int more_flag;
		auto size_more_flag = sizeof(more_flag);
		int step = 0;
		do {
			zmq_msg_t *zmsg = new zmq_msg_t;
			CHECK(zmq_msg_init(zmsg) == 0) << zmq_strerror(errno);
			while (true) {
				if (zmq_msg_recv(zmsg, receiver, 0) != -1) break;
				if (errno == EINTR) continue;  // may be interupted by google profiler
				LOG(WARNING)
				        << "[Bus::recv_thread] failed to receive message. errno: "
				        << zmq_strerror(errno);
				return;
			}
			char* buf = CHECK_NOTNULL((char *)zmq_msg_data(zmsg)); //void * to char *
			size_t size = zmq_msg_size(zmsg);

			if (step == 0) {
				CHECK(msg->msg_header.ParseFromArray(buf, size))
					<< "[Bus::recv_thread]: failed to paser msg_header";
				LOG(INFO) << "[Bus::recv_thread]: Got a msg from mode_id = "
					<< msg->msg_header.from_id();
			}
			else {
				DataSlice recv_data_slice(buf, size); //char * to string
				msg->data_slice_list.push_back( std::move(recv_data_slice) );
			}
			++step;
			CHECK(zmq_getsockopt (receiver, ZMQ_RCVMORE, &more_flag, &size_more_flag) == 0)
				<< zmq_strerror(errno);
		} while(more_flag); //sendmore
		Tracker::get_mutable_instance().push_into_pending_msg(msg);
	}
}
