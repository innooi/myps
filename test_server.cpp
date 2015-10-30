#include <cstdio>
#include <iostream>
#include <string>
#include <zmq.h>

void free_data(void *, void *) {

}

int main() {
	void *context = zmq_ctx_new();
	zmq_ctx_set(context, ZMQ_MAX_SOCKETS, 65536);
	void *receiver = zmq_socket(context, ZMQ_PULL);
	zmq_bind(receiver, "tcp://*:34567");

	int more;
	size_t more_size = sizeof(more);

	while(true) {
		do {
			zmq_msg_t *zmsg = new zmq_msg_t;
			zmq_msg_init(zmsg);
			zmq_msg_recv(zmsg, receiver, 0);
			char *buf = (char *) zmq_msg_data(zmsg);
			size_t size = zmq_msg_size(zmsg);
			std::cout << std::string(buf, size) << std::endl;
			zmq_getsockopt (receiver, ZMQ_RCVMORE, &more, &more_size);
			zmq_msg_close(zmsg);
		} while(more);
		puts("");
	}

	zmq_close(receiver);
	zmq_ctx_destroy(context);

	return 0;
}