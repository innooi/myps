#pragma once

#include "common.h"

class Bus {
private:
	uint64_t node_msg_id;
	std::unordered_map<uint64_t, std::function<int(SPMsg)> > msg_id_to_callback;

	uint32_t my_node_id_;
	std::unordered_map<uint32_t, void *> senders_;
	uint32_t num_elem_in_queue_;
	std::queue<SPMsg> PQ_[QUEUE_LEVEL];
	//need an atomic queue

	void *context_; //zmq context
	void *receiver_;

	std::mutex mutex_queue_; //prevent the queue
	std::condition_variable cond_exist_elem_queue_; //notify the sendthread to send elem
	boost::lockfree::queue< SPMsg > recvQueue;
	std::thread *sendThread, *recvThread;

	void SendThread(); //daemon thread for sending msg
	void RecvThread(); //daemon thread for receving msg

public:
	Bus();
	~Bus();

	//add a msg into multi-level priority queue, the default priority level is 4
	bool Send(SPMsg msg, std::function<int(SPMsg)> callback_function);
	bool Send(SPMsg msg, int priority, std::function<int(SPMsg)> callback_function);

	void Init(const NodeInfo &node_info);
	void Run();

	bool Connect(const NodeInfo &node_info);
	void Disconnect(const NodeInfo &node_info);

	static void FreeData(void *data, void *hint) {
		delete [] (char*) data;
	}

	static void nonFreeData(void *data, void *hint) {
		//do nothing, just a dummy function
	}
};
