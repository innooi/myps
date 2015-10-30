#pragma once

#include "common.h"
#include "node.h"
#include "bus.h"
#include "message.h"

class Tracker : public boost::serialization::singleton<Tracker> {
private:
	int tracker_id;
    std::unordered_map<uint64_t, std::function<void(void)> > msg_id_map_to_callback;
    std::thread *dispatch_thread_t;
    void process_thread(SPMsg);
	void do_dispatch(); /* daemon thread for dispatching messages */
	SPMsg create_sys_msg(MessagesHeader::ObjType p_from_obj_type,
						NodeId p_to_id,
						MessagesHeader::ObjType p_to_obj_type,
						MessagesHeader::PkgType p_pkg_type,
						MessagesHeader::SysMsgType p_sys_msg_type,
						int priority = (QUEUE_LEVEL - 1) / 2);
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
};
