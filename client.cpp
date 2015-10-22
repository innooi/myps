#include "common.h"
#include "bus.h"

int main(int argc, char** argv) {
	PS::Bus *myBus = new PS::Bus();
	
	PS::Node myNode;
	myNode.id = "Client";
	myNode.ip = "127.0.0.1";
	myNode.port = 54321;
	
	myBus->Init(myNode);

	PS::Node remoteNode;
	remoteNode.id = "Server";
	remoteNode.ip = "127.0.0.1";
	remoteNode.port = 65432;

	myBus->Connect(remoteNode);

	myBus->Run();

	PS::Message *msg = new PS::Message();
	msg->sender = "Client";
	msg->recever = "Server";
	msg->task.set_id("Client");
	msg->task.set_ip("127.0.0.1");
	msg->task.set_port(54321);
	msg->data = new char[20];
	strcpy(msg->data, "hello world!\0");
	msg->data_size = 13;

	myBus->Send(msg);

	msg = new PS::Message();

	msg->sender = "Client";
	msg->recever = "Server";
	msg->task.set_id("Client");
	msg->task.set_ip("127.0.0.1");
	msg->task.set_port(54321);
	msg->data = new char[20];
	strcpy(msg->data, "hahaha!\0");
	msg->data_size = 8;

	myBus->Send(msg);


	puts("have sent");

	myBus->Wait();

	return 0;
}
