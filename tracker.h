#pragma once

#include "common.h"

namespace PS{
	class Tracker {
	private:
		PS::Bus *bus;
		uint64_t node_msg_id;
		std::unordered_map<uint64_t, std::function> msg_id_to_callback;
		void RecvThread(); // the daemon thread
	public:
		Tracker();
		int Send(SPMsg msg, std::function callback_function);
	};
}
