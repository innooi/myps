#pragma once

#include "common.h"
#include "message.h"

enum class Role {
	WORKER,
	SERVER,
	NAMENODE	
};

enum class NodeState {
    LISTENING_REGISTER,
    REGISTER_SENT,
    NODE_LIST_SENT,
    NODE_LIST_REVD,
    LISTENING_JOB,
    COMPUTING,
    CLOSED
};

class NodeInfo {
    friend class boost::serialization::access;

    template<class Archive>
    void serialize(Archive & ar, const unsigned int version);
public:
    Role role;
    NodeId node_id;
    std::string ip;
    uint32_t port;
    
    NodeInfo();
    NodeInfo(Role, NodeId);
    NodeInfo(Role, NodeId, const std::string &, uint32_t);
};

class Node {
protected:
    NodeState state;
    std::vector< std::shared_ptr<NodeInfo> > node_list;
    std::unordered<NodeId, std::shared_ptr<NodeInfo> > id_map_to_info;
public:
    virtual void process_msg(SPMsg) = 0;
    virtual void init(NodeId, const std::string &, uint32_t) = 0;
    virtual void run() = 0;  
    virtual ~Node() = 0;
};

class Worker:   public NodeInfo, 
                public Node, 
                public boost::serialization::singleton<Worker> {
public:
    virtual void process_msg(SPMsg);
    virtual void process_sys_msg(SPMsg);
    virtual void process_usr_msg(SPMsg);
    virtual void init(NodeId, const std::string &, uint32_t);
    virtual void run();
    virtual ~Worker();
};

class Server : public Node, public boost::serialization::singleton<Server> {
public:
    virtual void process_msg(SPMsg);
    virtual void process_sys_msg(SPMsg);
    virtual void process_usr_msg(SPMsg);
    virtual void init(NodeId, const std::string &, uint32_t);
    virtual void run();
    virtual ~Server();
};

class NameNode : public Node, public boost::serialization::singleton<NameNode> {
private:
    uint32_t num_got_node_list_ack;
    std::mutex mtx_node_list_ack;
    std::condition_variable cond_got_all_node_list_ack;
public:
    virtual void process_msg(SPMsg);
    virtual void process_sys_msg(SPMsg);
    virtual void process_usr_msg(SPMsg);
    virtual void init(NodeId, const std::string &, uint32_t);
    virtual void run();
    virtual ~NameNode();
};
