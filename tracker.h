#pragma once

#include "common.h"
#include "node.h"
#include "message.h"
#include "bus.h"

class Bus;

class Tracker : public boost::serialization::singleton<Tracker> {
private:
	friend class Bus;

	int tracker_id;
    std::unordered_map<uint64_t, std::function<void(void)> > msg_id_map_to_callback;
    std::thread *dispatch_thread_t;
    void process_func(SPMsg);
    Node *node;
    Bus *bus;
public:
	int init(Node *, Bus *);
	int run();
	int send_msg(SPMsg);
	int send_msg(SPMsg, std::function<void(void)>);
	SPMsg create_sys_msg(MessageHeader::ObjType p_from_obj_type,
						NodeId p_to_id,
						MessageHeader::ObjType p_to_obj_type,
						MessageHeader::PkgType p_pkg_type,
						MessageHeader::SysMsgType p_sys_msg_type,
						int priority = (PRIORITY_LEVEL - 1) / 2);
};
