#include "common.h"
//#include "node.h"
//#include "bus.h"
//#include "tracker.h"

DEFINE_string(id, "", "node id");
DEFINE_string(ip, "", "node ip address");
DEFINE_int32(port, 0, "node bus port");

int main(int argc, char **argv) {
    ::google::ParseCommandLineFlags(&argc, &argv, true);
    if (FLAGS_id == "" || FLAGS_ip == "" || FLAGS_port == 0) {
        std::cout << "undefined argv." << std::endl;
        return 0;
    }
    std::cout << "Worker " << FLAGS_id << " running on " << FLAGS_ip << " " << FLAGS_port << std::endl;
    LOG(INFO) << "Worker " << FLAGS_id << " running on " << FLAGS_ip << " " << FLAGS_port;

    
    return 0;
}
