#include "node.h"

template<class Archive>
void NodeInfo::serialize(Archive & ar, unsigned int version) {
	ar & role;
	ar & node_id;
	ar & ip;
	ar & port;
}

NodeInfo::NodeInfo() {
}

NodeInfo::NodeInfo(Role p_role, NodeId p_node_id)
	: role(p_role), node_id(p_node_id) {	
}

NodeInfo::NodeInfo(Role p_role, NodeId p_node_id, 
	const std::string &p_ip, uint32_t p_port)
	: role(p_role), node_id(p_node_id), ip(p_ip), port(p_port) {
}
