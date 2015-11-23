#include "node.h"
#include "bus.h"
#include "tracker.h"

void NameNode::process_msg(SPMsg msg) {
	if (msg->msg_header.msg_level() == MessageHeader::SYS_MSG) {
		process_sys_msg(msg);
	} else if (msg->msg_header.msg_level() == MessageHeader::USR_MSG) {
		//process user-defined msg
		process_usr_msg(msg);
	} else {
		LOG(ERROR) << "[NameNode::process_msg]: Invalid msg_level.";
		return;
	}
}

void NameNode::process_sys_msg(SPMsg msg) {
	switch (msg->msg_header.sys_msg_type()) {
		case MessageHeader::REGISTER_NODE: {
			if (msg->msg_header.pkg_type() == MessageHeader::PUSH) {
				auto it_first_ele_in_list = msg->data_slice_list.begin();
				std::stringstream ss(*it_first_ele_in_list);
				boost::archive::binary_iarchive ia(ss);
				auto p_node_info = std::make_shared<NodeInfo>();
				ia >> *p_node_info;
				node_list.push_back(p_node_info);
				id_map_to_info[p_node_info->node_id] = p_node_info;
				LOG(INFO) << "[NameNode::process_sys_msg]: Get a REGISTER from " + p_node_info->node_id;
			} else {
				LOG(ERROR) << "[NameNode::process_sys_msg]: Invalid pkg_type when got a REGISTER msg";
				return;
			}
			break;
		}
		case MessageHeader::NODE_LIST_ACK: {
			if (msg->msg_header.pkg_type() == MessageHeader::PUSH) {
				LOG(INFO) << "[NameNode::process_sys_msg]: Get a NODE_LIST_ACK";
				std::unique_lock<std::mutex> lock(mtx_node_list_ack);
				if (++num_got_node_list_ack == node_list.size()) {
					lock.unlock();
					cond_got_all_node_list_ack.notify_one();
				} else {
					lock.unlock();
				}
			} else {
				LOG(ERROR) << "[NameNode::process_sys_msg]: Invalid pkg_type when got a NODE_LIST_ACK";
				return;
			}
			break;
		}
		default: {
			LOG(ERROR) << "[NameNode::process_sys_msg]: Invalid sys_msg_type";
			return;
		}
	}
}

void NameNode::process_usr_msg(SPMsg msg) {

}

void NameNode::init(NodeId p_node_id, const std::string &p_ip, uint32_t p_port) {
	my_info.role = Role::NAMENODE;
	my_info.node_id = p_node_id;
	my_info.ip = p_ip;
	my_info.port = p_port;
	state = NodeState::CLOSED;
	node_list.clear();
	id_map_to_info.clear();
	num_got_node_list_ack = 0;
	LOG(INFO) << "[NameNode::init]: " << p_node_id << " running on " << p_ip << ":" << p_port;
}

void NameNode::run() {
	state = NodeState::LISTENING_REGISTER;
	LOG(INFO) << "[NameNode::run]: LISTENING_REGISTER";
	//wait for register, shuold use sleep
	sleep(REGISTER_WAIT_TIME_IN_SEC);
	
	//wait for node list ack, a condional variable
	auto& tracker_ins = Tracker::get_mutable_instance();
	
	//prepare the sent message
	std::stringstream ss;
	boost::archive::binary_oarchive oa(ss);
	size_t node_list_size = node_list.size();
	oa << node_list_size;
	for (auto node_list_ele:node_list) {
		oa << *node_list_ele;
	}
	std::string node_list_str = ss.str();

	for (auto node_list_ele:node_list) {
		SPMsg msg = tracker_ins.create_sys_msg(	MessageHeader::NODE,
												node_list_ele->node_id,
												MessageHeader::NODE,
												MessageHeader::PUSH,
												MessageHeader::NODE_LIST_DATA);
		msg->data_slice_list.push_back(node_list_str);
		tracker_ins.send_msg(msg);
	}
	state = NodeState::NODE_LIST_SENT;
	LOG(INFO) << "[NameNode::run]: NODE_LIST_SENT";

	num_got_node_list_ack = 0;
	std::unique_lock<std::mutex> lck(mtx_node_list_ack);
	while(num_got_node_list_ack != node_list.size()) {
		cond_got_all_node_list_ack.wait(lck);
	}
	lck.unlock();
	//got all ack, so it's ready to work
	for (auto node_list_ele:node_list) {
		SPMsg msg = tracker_ins.create_sys_msg(	MessageHeader::NODE,
												node_list_ele->node_id,
												MessageHeader::NODE,
												MessageHeader::PUSH,
												MessageHeader::STARTUP_READY);
		tracker_ins.send_msg(msg);
	}
	state = NodeState::LISTENING_JOB;
	LOG(INFO) << "[NameNode::run]: LISTENING_JOB";
}

NameNode::~NameNode() {

}