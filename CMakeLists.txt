cmake_minimum_required(VERSION 3.3)
project(ParameterServer)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    bus.cpp
    bus.h
    common.h
    main.cpp
    makefile
    message.h
    message_header.pb.cc
    message_header.pb.h
    node.h
    node_info.cpp
    test_client.cpp
    test_server.cpp
    tracker.cpp
    tracker.h
    worker.cpp)

add_executable(ParameterServer ${SOURCE_FILES})