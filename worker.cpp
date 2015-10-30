#include "node.h"
#include "bus.h"
#include "tracker.h"

void Worker::process_msg(SPMsg msg) {
	if (msg->msg_header.msg_level() == MessagesHeader::SYS_MSG) {
		process_sys_msg(msg);
	}
	else if (msg->msg_header.msg_level() == MessagesHeader::USR_MSG) {
		//process user-defined msg
		process_usr_msg(msg);
	}
	else {
		LOG(ERROR) << "[Worker::process_msg]: Invalid msg_level.";
		return;
	}
}

void Worker::process_sys_msg(SPMsg msg) {
	switch (msg->msg_header.sys_msg_type()) {
		case MessagesHeader::NODE_LIST_DATA: {
			if (msg->msg_header.pkg_type() == MessagesHeader::PUSH) {
				if (state != NodeState::REGISTER_SENT) {
					LOG(ERROR) << "[Worker::process_sys_msg]: Got NODE_LIST when state != REGISTER_SENT.";
					return;
				}
				state = NodeState::NODE_LIST_REVD;
				LOG(INFO) << "[Worker::process_sys_msg]: Got node_list";
				auto it_first_ele_in_list = msg->data_slice_list.begin();
				std::stringstream ss(*it_first_ele_in_list);
				boost::archive::binary_iarchive ia(ss);
				size_t size;
				ia >> size;
				for (auto i = 0; i < size; ++i) {
					auto p_node_info = std::make_shared<NodeInfo>();
					ia >> *p_node_info;
					node_list.push_back(p_node_info);
					id_map_to_info[p_node_info->node_id] = p_node_info;
				}
				auto& tracker_ins = Tracker::get_mutable_instance();
				SPMsg = tracker_ins.create_sys_msg(	MessagesHeader::NODE,
													namenode_id,
													MessagesHeader::NODE,
													MessagesHeader::PUSH,
													MessagesHeader::NODE_LIST_ACK);
				tracker_ins.send_msg(msg);
				LOG(INFO) << "[Worker::process_sys_msg]: Send NODE_LIST_ACK";
			}
			else {
				LOG(ERROR) << "[Worker::process_sys_msg]: Invalid pkg_type for NODE_LIST_DATA";
				return;
			}
			break;	
		}

		case MessagesHeader::STARTUP_READY: {
			if (msg->msg_header.pkg_type() == MessagesHeader::PUSH) {
				if (state != NodeState::NODE_LIST_REVD) {
					LOG(ERROR) 
						<< "[Worker::process_sys_msg]: Get STARTUP_READY when state != NODE_LIST_REVD";
					return;
				}
				state = NodeState::LISTENING_JOB;
			}
			else {
				LOG(ERROR) << "[Worker::process_sys_msg]: Invalid pkg_type for STARTUP_READY";
				return;	
			}
			break;
		}

		default: {
			LOG(ERROR) << "[Worker::process_sys_msg]: Invalid sys_msg_type";
			return;
		}
	}
}

void Worker::process_usr_msg(SPMsg msg) {
	
}

void Worker::init(NodeId p_node_id, const std::string &p_ip, uint32_t p_port) {
	//how to get the node_id of namenode?

	role = Role::WORKER;
	node_id = p_node_id;
	ip = p_ip;
	port = p_port;
	state = NodeState::CLOSED;
	node_list.clear();
	id_map_to_info.clear();

	//register start
	auto& tracker_ins = Tracker::get_mutable_instance();
	SPMsg msg = tracker_ins.create_sys_msg(	MessagesHeader::NODE,
											namenode_id,
											MessagesHeader::NODE,
											MessagesHeader::PUSH,
											MessagesHeader::REGISTER_NODE);
	//push my node info into data slice list
	std::stringstream ss;
	boost::archive::binary_oarchive oa(ss);
	NodeInfo my_node_info(Role::WORKER, p_node_id, p_ip, p_port);
	oa << my_node_info;
	std::string my_node_info_str = ss.str();
	msg->data_slice_list.push_back(my_node_info_str);

	tracker_ins.send_msg(msg);
	state = NodeState::REGISTER_SENT;
	LOG(INFO) << "[Worker::init]: REGISTER_SENT";
	//wait the node_list sent from namenode
}

void Worker::run() {
	
}

Worker::~Worker() {

}
