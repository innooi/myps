#pragma once

#include "common.h"
#include "message_header.pb.h"

using DataSlice = std::string;

struct Message {
	MessageHeader msg_header;
	std::list<DataSlice> data_slice_list;
};

using SPMsg = std::shared_ptr<Message>;