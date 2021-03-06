#include "tracker.h"

void Tracker::process_func(SPMsg msg) {
	switch(msg->msg_header.to_obj_type()) {
		case MessageHeader::NODE:
			if (Role::WORKER == node->my_info.role) {
				Worker::get_mutable_instance().process_msg(msg);
			} else if (Role::SERVER == node->my_info.role) {
				Server::get_mutable_instance().process_msg(msg);	
			} else if (Role::NAMENODE == node->my_info.role) {
				NameNode::get_mutable_instance().process_msg(msg);		
			} else {
				LOG(ERROR) << "[Tracker::process_thread]: unknown node role";
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
			LOG(ERROR) << "[Tracker::process_thread]: unknown msg object type";
			return;
	}
	if (msg_id_map_to_callback.find(msg->msg_header.rpl_tracker_id()) 
		!= msg_id_map_to_callback.end()) {
		msg_id_map_to_callback[msg->msg_header.rpl_tracker_id()]();
		msg_id_map_to_callback.erase(msg->msg_header.rpl_tracker_id());
	}
	//free SPMsg here
}

SPMsg Tracker::create_sys_msg(MessageHeader::ObjType p_from_obj_type,
								NodeId p_to_id,
								MessageHeader::ObjType p_to_obj_type,
								MessageHeader::PkgType p_pkg_type,
								MessageHeader::SysMsgType p_sys_msg_type,
								int priority) {
	SPMsg ret(new Message);
	ret->msg_header.set_from_id(node->my_info.node_id);
	ret->msg_header.set_from_ip(node->my_info.ip);
	ret->msg_header.set_from_port(node->my_info.port);
	ret->msg_header.set_to_obj_type(p_from_obj_type);
	ret->msg_header.set_to_id(p_to_id);

	if (node->id_map_to_info.find(p_to_id) == node->id_map_to_info.end()) {
		LOG(ERROR) << "[Tracker::create_sys_msg]: Invalid to_node_id " + p_to_id;
		ret.reset();
		return ret;
	}
	std::shared_ptr<NodeInfo> p_info = node->id_map_to_info[p_to_id];
	ret->msg_header.set_to_id(p_info->node_id);
	ret->msg_header.set_to_ip(p_info->ip);
	ret->msg_header.set_to_port(p_info->port);
	ret->msg_header.set_to_obj_type(p_to_obj_type);
	ret->msg_header.set_msg_level(MessageHeader::SYS_MSG);
	ret->msg_header.set_pkg_type(p_pkg_type);
	ret->msg_header.set_sys_msg_type(p_sys_msg_type);
	ret->msg_header.set_priority(priority);
	return ret;
}

int Tracker::init(Node *p_node, Bus *p_bus) {
	tracker_id = 0;
	msg_id_map_to_callback.clear();
	node = p_node;
	bus = p_bus;
	return 0;
}

int Tracker::run() {
	if (nullptr == bus) {
		LOG(ERROR) << "[Tracker::run]: Uninitialized bus.";
		return 1;
	}
	return 0;
}

int Tracker::send_msg(SPMsg msg) {
	if (nullptr == bus) {
		LOG(ERROR) << "[Tracker::run]: Uninitialized bus.";
		return 1;
	}
	++tracker_id;
	msg->msg_header.set_tracker_id(tracker_id);
	if (false == bus->send_msg(msg)) {
		//bus->connect(msg->msg_header.to_id());
		bus->connect( *( node->id_map_to_info[msg->msg_header.to_id()] ) );
		bus->send_msg(msg);
	}
	return 0;
}

int Tracker::send_msg(SPMsg msg, std::function<void(void)> callback_function) {
	if (nullptr == bus) {
		LOG(ERROR) << "[Tracker::run]: Uninitialized bus.";
		return 1;
	}
	++tracker_id;
	msg->msg_header.set_tracker_id(tracker_id);
	msg_id_map_to_callback[tracker_id] = callback_function;
	if (false == bus->send_msg(msg)) {
		bus->connect( *( node->id_map_to_info[msg->msg_header.to_id()] ) );
		bus->send_msg(msg);
	}
	return 0;
}
