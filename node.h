#pragma once

#include "common.h"

enum class Role {
	WORKER,
	SERVER,
	NAMENODE	
};

class Node {
public:
	virtual const Role role() = 0;
   	virtual const NodeId node_id() = 0;
   	virtual const int rank() = 0;
   	virtual send_msg(SPMsg, std::function<void(void)>) = 0;
   	virtual process_msg(SPMsg) = 0;
   	virtual init() = 0;
   	virtual run() = 0;
};