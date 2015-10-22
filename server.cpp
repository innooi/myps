#include "common.h"
#include "bus.h"

int main(int argc, char** argv) {
	PS::Bus *myBus = new PS::Bus();
	
	PS::Node myNode;
	myNode.id = "Server";
	myNode.ip = "127.0.0.1";
	myNode.port = 65432;

	myBus->Init(myNode);

	myBus->Run();

	myBus->Wait();
	return 0;
}

