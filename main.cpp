#include "common.h"
#include "bus.h"
#include "node.hpp"

int main(int argc, char** argv) {
	PS::MyNode x;
	x.Init("1", "1", 1234);
	return 0;
}
