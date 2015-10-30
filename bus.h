#pragma once 

#include "common.h"
#include "node.h"
#include "tracker.h"
#include "message.h"

class Bus : public boost::serialization::singleton<Bus> {
private:
    NodeId my_node_id;
	std::unordered_map<NodeId, void *> senders;
	uint32_t num_elem_in_queue;
	std::queue<SPMsg> PQ[PRIORITY_LEVEL];

	void *context; //zmq context
	void *receiver;

	std::mutex mutex_queue; //prevent the queue
    //notify the sendthread to send elem
	std::condition_variable cond_exist_elem_queue; 
	boost::lockfree::queue< SPMsg > recvQueue;
	std::thread *send_thread_t, *recv_thread_t;

	void send_thread(); //daemon thread for sending msg
	void recv_thread(); //daemon thread for receving msg
	
	Tracker *tracker;	
public:
	//add a msg into multi-level priority queue, the default priority level is 4
	int send_msg(SPMsg msg, uint32_t priority_level = (PRIORITY_LEVEL - 1) / 2);

	void init(const NodeInfo &node_info);
	void run();

	bool connect(const NodeInfo &node_info);
    bool Disconnect(const NodeInfo &node_info);

    void free_data(void *, void *);
    void non_free_data(void *, void *);
};
