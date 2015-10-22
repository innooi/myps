#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <thread>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <sys/time.h>
#include <sys/mman.h>
#include <ifaddrs.h>
#include <assert.h>
#include <net/if.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netdb.h>

// smart pointers
#include <memory>
// stream
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <streambuf>
// containers
#include <vector>
#include <list>
#include <queue>
#include <map>
#include <unordered_map>
#include <unordered_set>
#include <set>
#include <algorithm>

// base
#include <google/protobuf/stubs/common.h>
#include "google/protobuf/text_format.h"

// google staff
#include "gflags/gflags.h"
#include "glog/logging.h"

//boost
#include <boost/thread.hpp>
#include <boost/thread/lock_factories.hpp>
#include <boost/lockfree/queue.hpp>
#include <boost/shared_ptr.hpp>

//zmq
#include <zmq.h>

//yaml-cpp
#include "yaml-cpp/yaml.h"
