#include "common.h"
#include "node.h"
#include "bus.h"
#include "tracker.h"

DEFINE_string(id, "", "node id");
DEFINE_string(ip, "", "node ip address");
DEFINE_int32(port, 0, "node bus port");

DEFINE_string(name_node_id, "", "name_node id");
DEFINE_string(name_node_ip, "", "name_node ip address");
DEFINE_int32(name_node_port, 0, "name_node bus port");

int main(int argc, char **argv) {
    ::google::ParseCommandLineFlags(&argc, &argv, true);
    LOG(INFO) << "Worker " << FLAGS_id << " running on " << FLAGS_ip << " " << FLAGS_port;

    auto& worker_ins = Worker::get_mutable_instance();
    worker_ins.init(FLAGS_id, FLAGS_ip, FLAGS_port,
        FLAGS_name_node_id, FLAGS_name_node_ip, FLAGS_name_node_port);

    auto& bus_ins = Bus::get_mutable_instance();
    bus_ins.init(worker_ins.my_info);

    auto& tracker_ins = Tracker::get_mutable_instance();
    tracker_ins.init(&worker_ins, &bus_ins);

    tracker_ins.run();
    bus_ins.run();
    worker_ins.run();
    return 0;
}
