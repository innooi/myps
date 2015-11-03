CC = g++
CFLAGS = -std=c++11 -O2

LDFLAGS = -L/usr/local/lib -lzmq -lglog -lgflags -lprotobuf -lboost_system \
-lboost_filesystem -lboost_thread -lboost_serialization -lyaml-cpp

INCLUDE_PATH = -I./ -I/usr/local/boost_1_58_0/boost -I/usr/local/include

HEADER = $(wildcard *.h) message_header.pb.h

CPP_SRC = $(wildcard *.cc)

CPP_OBJ = ${CPP_SRC:.cc=.o} message_header.pb.o

#EXE = namenode_ins server_ins worker_ins
EXE = main

PROTOC = protoc -I=./ --cpp_out=./ 

all: ${EXE}

message_header.pb.h message_header.pb.cc: message_header.proto
	${PROTOC} message_header.proto

${CPP_OBJ}: %.o: %.cc ${HEADER}
	${CC} ${CFLAGS} ${INCLUDE_PATH} -c $<

main: main.o bus.o namenode.o worker.o node.o server.o\
	message_header.pb.o node_info.o tracker.o
	${CC} ${LDFLAGS} -o main main.o bus.o node.o \
	namenode.o worker.o server.o message_header.pb.o node_info.o tracker.o

namenode_ins: namenode_ins.o bus.o namenode.o worker.o server.o node.o \
	message_header.pb.o node_info.o tracker.o
	${CC} ${LDFLAGS} -o namenode_ins namenode_ins.o bus.o server.o node.o \
	namenode.o worker.o message_header.pb.o node_info.o tracker.o

server_ins: server_ins.o bus.o namenode.o worker.o server.o \
	message_header.pb.o node.o node_info.o tracker.o
	${CC} ${LDFLAGS} -o server_ins server_ins.o bus.o namenode.o \
	node.o worker.o message_header.pb.o node_info.o tracker.o

worker_ins: worker_ins.o bus.o namenode.o worker.o server.o message_header.pb.o \
	node.o node_info.o tracker.o
	${CC} ${LDFLAGS} -o worker_ins worker_ins.o bus.o namenode.o \
	node.o server.o worker.o message_header.pb.o node_info.o tracker.o

clean:
	rm -rf *.o message_header.pb.cc

.PHONY: clean
