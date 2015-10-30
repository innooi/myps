#pragma once

#include "common.h"
#include "message_header.pb.h"

using DataSlice = std::string;
using SPMsg = std::shared_ptr<Message>;

struct Message {
	MessageHeader msg_header;
	std::list<DataSlice> data_slice_list;
};
