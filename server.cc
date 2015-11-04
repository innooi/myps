#include "node.h"
#include "bus.h"
#include "tracker.h"

void Server::process_msg(SPMsg msg) {
	if (msg->msg_header.msg_level() == MessageHeader::SYS_MSG) {
		process_sys_msg(msg);
	} else if (msg->msg_header.msg_level() == MessageHeader::USR_MSG) {
		//process user-defined msg
		process_usr_msg(msg);
	} else {
		LOG(ERROR) << "[Server::process_msg]: Invalid msg_level.";
		return;
	}
}

void Server::process_sys_msg(SPMsg msg) {
	switch (msg->msg_header.sys_msg_type()) {
		case MessageHeader::NODE_LIST_DATA: {
			if (msg->msg_header.pkg_type() == MessageHeader::PUSH) {
				if (state != NodeState::REGISTER_SENT) {
					LOG(ERROR) << "[Server::process_sys_msg]: Got NODE_LIST when state != REGISTER_SENT.";
					return;
				}
				state = NodeState::NODE_LIST_REVD;
				LOG(INFO) << "[Server::process_sys_msg]: Got node_list";
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
				SPMsg msg = tracker_ins.create_sys_msg(	MessageHeader::NODE,
														sp_name_node_info->node_id,
														MessageHeader::NODE,
														MessageHeader::PUSH,
														MessageHeader::NODE_LIST_ACK);
				tracker_ins.send_msg(msg);
				LOG(INFO) << "[Server::process_sys_msg]: Send NODE_LIST_ACK";
			} else {
				LOG(ERROR) << "[Server::process_sys_msg]: Invalid pkg_type for NODE_LIST_DATA";
				return;
			}
			break;	
		}
		case MessageHeader::STARTUP_READY: {
			if (msg->msg_header.pkg_type() == MessageHeader::PUSH) {
				if (state != NodeState::NODE_LIST_REVD) {
					LOG(ERROR) 
						<< "[Server::process_sys_msg]: Get STARTUP_READY when state != NODE_LIST_REVD";
					return;
				}
				state = NodeState::LISTENING_JOB;
			} else {
				LOG(ERROR) << "[Server::process_sys_msg]: Invalid pkg_type for STARTUP_READY";
				return;	
			}
			break;
		}
		default: {
			LOG(ERROR) << "[Server::process_sys_msg]: Invalid sys_msg_type";
			return;
		}
	}
}

void Server::process_usr_msg(SPMsg msg) {

}

void Server::init(NodeId p_node_id, const std::string &p_ip, uint32_t p_port,
	NodeId p_name_node_id, const std::string &p_name_node_ip, uint32_t p_name_node_port) {
	my_info.role = Role::SERVER;
	my_info.node_id = p_node_id;
	my_info.ip = p_ip;
	my_info.port = p_port;
	state = NodeState::CLOSED;
	node_list.clear();
	id_map_to_info.clear();
	
    //how to get the node_id of namenode?
    sp_name_node_info = std::make_shared<NodeInfo>(Role::NAMENODE, p_name_node_id,
        p_name_node_ip, p_name_node_port);
    node_list.push_back(sp_name_node_info);
    id_map_to_info[p_name_node_id] = sp_name_node_info; 
}

void Server::run() {
	//register start
	auto& tracker_ins = Tracker::get_mutable_instance();
	SPMsg msg = tracker_ins.create_sys_msg(	MessageHeader::NODE,
											sp_name_node_info->node_id,
											MessageHeader::NODE,
											MessageHeader::PUSH,
											MessageHeader::REGISTER_NODE);
	std::stringstream ss;
    boost::archive::binary_oarchive oa(ss);
    NodeInfo my_node_info(Role::SERVER, my_info.node_id, my_info.ip, my_info.port);
    oa << my_node_info;
    std::string my_node_info_str = ss.str();
    msg->data_slice_list.push_back(my_node_info_str);

	tracker_ins.send_msg(msg);
	state = NodeState::REGISTER_SENT;
	LOG(INFO) << "[Server::init]: REGISTER_SENT";
	//wait the node_list sent from namenode
}

Server::~Server() {

}