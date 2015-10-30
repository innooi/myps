#include "tracker.h"

void Tracker::process_thread(SPMsg msg) {
	switch(msg->msg_header.to_obj_type()) {
		case MessageHeader::NODE:
			if (Role::WORKER == node->role) {
				WORKER::process_msg(msg);
			}
			else if (Role::SERVER == node->role) {
				//SERVER::process_msg(msg);	
			}
			else if (Role::NAMENODE == node->role) {
				//NAMENODE::process_msg(msg);		
			}
			else {
				LOG(ERROR) << "[Tracker::dispatch_thread]: unknown node role";
				return;
			}
			break;
		case MessageHeader::FILED:
			break;
		case MessageHeader::CACHE:
			break;
		case MessageHeader::ENGINE:
			break;
		default:
			LOG(ERROR) << "[Tracker::dispatch_thread]: unknown msg object type";
			return;
	}
	if (msg_id_map_to_callback.find(msg->msg_header.rpl_tracker_id()) 
		!= msg_id_map_to_callback.end()) {
		msg_id_map_to_callback[msg->msg_header.rpl_tracker_id()]();
		msg_id_map_to_callback.erase(msg->msg_header.rpl_tracker_id());
	}
	//free SPMsg here
}

void Tracker::dispatch_thread() {
	for (;;) {
		std::unique_lock<std::mutex> lk(pending_msg_mutex);
		for (; num_pending_msg == 0;) {
			cond_exist_pending_msg.wait(lk);
		}
		SPMsg msg = pending_msg.front();
		pending_msg.pop();
		--num_pending_msg;
		lk.unlock();
		
		LOG(INFO) << "[Tracker::dispatch_thread]: dispatch_thread gets a msg."
		
		//create a new thread to process
		std::thread *process_thread_t =
			new std::thread( std::bind(&Tracker::process_thread, this, msg) );
		process_thread_t->detach();
	}
}

SPMsg Tracker::create_sys_msg(MessagesHeader::ObjType p_from_obj_type,
								NodeId p_to_id,
								MessagesHeader::ObjType p_to_obj_type,
								MessagesHeader::PkgType p_pkg_type,
								MessagesHeader::SysMsgType p_sys_msg_type,
								int priority = (QUEUE_LEVEL - 1) / 2) {
	SPMsg ret(new MessagesHeader());
	ret->msg_header.set_from_id(node->node_id);
	ret->msg_header.set_from_ip(node->ip);
	ret->msg_header.set_from_port(node->port);
	ret->msg_header.set_from_port(p_from_obj_type);
	ret->msg_header.set_to_id(p_to_id);
	if (node->id_map_to_info.find(p_to_id) == node->id_map_to_info.end()) {
		LOG(ERROR) << "[Tracker::create_sys_msg]: Invalid to_node_id."
		ret.reset();
		return ret;
	}
	std::shared_ptr<NodeInfo> p_info = node->id_map_to_info[p_to_id];
	ret->msg_header.set_to_id(p_info->node_id);
	ret->msg_header.set_to_ip(p_info->ip);
	ret->msg_header.set_to_port(p_info->port);
	ret->msg_header.set_to_obj_type(p_to_obj_type);
	ret->msg_header.set_msg_level = MessagesHeader::SYS_MSG;
	ret->msg_header.set_sys_msg_type(p_sys_msg_type);
	ret->msg_header.set_priority(priority);
	return ret;
}

void Tracker::empty_func() {
}

int Tracker::init(Node *p_node, Bus *p_bus) {
	tracker_id = 0;
	msg_id_map_to_callback.clear();
	dispatch_thread_t = null_ptr;
	num_pending_msg = 0;
	while (pending_msg.pop());
	node = p_node;
	bus = p_bus;
	return 0;
}

int Tracker::run() {
	if (null_ptr == bus) {
		LOG(ERROR) << "[Tracker::run]: Uninitialized bus.";
		return 1;
	}
	if (null_ptr == dispatch_thread_t) {
		dispatch_thread_t = new std::thread(&Tracker::dispatch_thread, this);
		dispatch_thread_t->detach();
		LOG(INFO) << "[Tracker::run]: do_dispatch thread has started successfully.";
		return 0;
	}
	else {
		LOG(ERROR)
			<< "[Tracker::run]: do_dispatch thread has not been started.";
		return 2;
	}
}

int Tracker::send_msg(SPMsg msg) {
	if (null_ptr == bus) {
		LOG(ERROR) << "[Tracker::run]: Uninitialized bus.";
		return 1;
	}
	++tracker_id;
	msg->msg_header.set_tracker_id(tracker_id);
	if (false == bus->send_msg(msg)) {
		bus->connect(msg->msg_header.to_id());
		bus->send_msg(msg);
	}
	return 0;
}

int Tracker::send_msg(SPMsg msg, std::function<void(void)> callback_function) {
	if (null_ptr == bus) {
		LOG(ERROR) << "[Tracker::run]: Uninitialized bus.";
		return 1;
	}
	++tracker_id;
	msg->msg_header.set_tracker_id(tracker_id);
	msg_id_map_to_callback[tracker_id] = callback_function;
	if (false == bus->send_msg(msg)) {
		bus->connect(msg->msg_header.to_id());
		bus->send_msg(msg);
	}
	return 0;
}

int Tracker::push_into_pending_msg(SPMsg) {
	std::unique_lock<std::mutex> lk(pending_msg_mutex);
	pending_msg.push(SPMsg);
	++num_pending_msg;
	lk.unlock();
	if (1 == num_pending_msg) {
		cond_exist_pending_msg.notify_one();
	}
	return 0;
}
