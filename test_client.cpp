#include <cstdio>
#include <zmq.h>

void free_data(void *, void *) {

}

int main() {
	void *context = zmq_ctx_new();
	void *sender = zmq_socket(context, ZMQ_PUSH);
	zmq_connect(sender, "tcp://127.0.0.1:34567");
	int tag = ZMQ_SNDMORE;

	char *id_buf = "my id";
	zmq_setsockopt (sender, ZMQ_IDENTITY, id_buf, sizeof(id_buf));

	zmq_msg_t *first_msg = new zmq_msg_t;
	char *first_buf = "the first msg";
	zmq_msg_init_data(first_msg, first_buf, sizeof(first_buf), free_data, NULL);

	zmq_msg_send(first_msg, sender, tag);
	
	zmq_msg_t *second_msg = new zmq_msg_t;
	char *second_buf = "the second msg";
	zmq_msg_init_data(second_msg, second_buf, sizeof(second_buf), free_data, NULL);

	zmq_msg_send(second_msg, sender, tag);

	tag = ZMQ_DONTWAIT;

	zmq_msg_t *third_msg = new zmq_msg_t;
	char *third_buf = "the third msg";
	zmq_msg_init_data(third_msg, third_buf, sizeof(third_buf), free_data, NULL);
	zmq_msg_send(third_msg, sender, tag);

	tag = ZMQ_SNDMORE;

	zmq_msg_t *forth_msg = new zmq_msg_t;
	char *forth_buf = "the forth msg";
	zmq_msg_init_data(forth_msg, forth_buf, sizeof(forth_buf), free_data, NULL);
	zmq_msg_send(forth_msg, sender, tag);	

	tag = ZMQ_DONTWAIT;
	
	zmq_msg_t *fifth_msg = new zmq_msg_t;
	char *fifth_buf = "the fifth msg";
	zmq_msg_init_data(fifth_msg, fifth_buf, sizeof(fifth_buf), free_data, NULL);
	zmq_msg_send(fifth_msg, sender, tag);		

	zmq_close(sender);
	zmq_ctx_destroy(context);

	return 0;
}