#pragma once

#include "common.h"
#include "node.h"
#include "message.h"
#include "bus.h"

class Bus;

class Tracker : public boost::serialization::singleton<Tracker> {
private:
	int tracker_id;
    std::unordered_map<uint64_t, std::function<void(void)> > msg_id_map_to_callback;
    std::thread *dispatch_thread_t;
    void process_func(SPMsg);
	void dispatch_thread(); /* daemon thread for dispatching messages */
	uint32_t num_pending_msg;
	std::mutex pending_msg_mutex;
    std::queue<SPMsg> pending_msg;
    std::condition_variable cond_exist_pending_msg;
    Node *node;
    Bus *bus;
public:
	int init(Node *, Bus *);
	int run();
	int send_msg(SPMsg);
	int send_msg(SPMsg, std::function<void(void)>);
	int push_into_pending_msg(SPMsg);
	SPMsg create_sys_msg(MessageHeader::ObjType p_from_obj_type,
						NodeId p_to_id,
						MessageHeader::ObjType p_to_obj_type,
						MessageHeader::PkgType p_pkg_type,
						MessageHeader::SysMsgType p_sys_msg_type,
						int priority = (PRIORITY_LEVEL - 1) / 2);
};
