#include "tracker.h"

namesapce PS {
	Tracker::Tracker() node_msg_id(0) {
		msg_to_callback.clear();	
	}

	int Tracker::Send(SPMsg msg, std::function callback_function) {
		msg_id_to_callback[node_msg_id] = callback_thread;
		msg->msg_header.set_msg_id(node_msg_id);
		++node_msg_id;
		bus->Send(msg);
	}

	void Tracker::RecvThread() {

	}
};