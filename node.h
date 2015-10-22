#pragma once

#include "common.h"
#include "bus.h"

class Node {
private:
	NodeInfo my_node_info;
	Bus *bus;
	std::unordered_map<NodeId, NodeInfo> node_id_to_addr;
public:
	virtual Node();
	virtual void init();
	virtual void run();
};

class WorkerNode : public Node {

};

class ServerNode : public Node {

};

class NameNode : public Node {

};
