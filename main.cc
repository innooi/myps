#include "common.h"
//#include "node.h"
//#include "bus.h"
//#include "tracker.h"

enum class Role {
	WORKER,
	SERVER,
	NAMENODE	
};

struct NodeInfo {
friend class boost::serialization::access;

    template<class Archive>
    void serialize(Archive & ar, unsigned int version) {
    	
    }
    
    Role role;
    NodeId node_id;
    std::string ip;
    uint32_t port;
    
    NodeInfo();
    NodeInfo(Role, NodeId);
    NodeInfo(Role, NodeId, const std::string &, uint32_t);
};

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

int main(int argc, char **argv) {
    //auto& worker_ins = Worker::get_mutable_instance();
    std::stringstream ss;
    boost::archive::binary_oarchive oa(ss);
    NodeInfo my_node_info(Role::WORKER, "sb_id", "250.250.250.250", 250);
    oa << my_node_info;
    boost::archive::binary_iarchive ia(ss);
    NodeInfo the_node_info;
    ia >> the_node_info;
    std::cout << the_node_info.node_id << std::endl;
    return 0;
}
