#include "common.h"
#include "node.h"
#include "bus.h"
#include "tracker.h"

DEFINE_string(id, "", "node id");
DEFINE_string(ip, "", "node ip address");
DEFINE_int32(port, 0, "node bus port");

int main(int argc, char **argv) {
    ::google::ParseCommandLineFlags(&argc, &argv, true);

    auto& name_node_ins = NameNode::get_mutable_instance();
    name_node_ins.init(FLAGS_id, FLAGS_ip, FLAGS_port);

    auto& bus_ins = Bus::get_mutable_instance();
    bus_ins.init(name_node_ins.my_info);

    auto& tracker_ins = Tracker::get_mutable_instance();
    tracker_ins.init(&name_node_ins, &bus_ins);

    bus_ins.run();
    tracker_ins.run();
    name_node_ins.run();
    return 0;
}
