CC = g++
CFLAGS = -Wall -std=c++11 -O2

LDFLAGS = -L/usr/local/lib -lzmq -lglog -lgflags -lprotobuf -lboost_system \
-lboost_filesystem -lboost_thread -lboost_serialization -lyaml-cpp

INCLUDE_PATH = -I./ -I/usr/local/boost_1_58_0/boost -I/usr/local/include

SRC = bus.cpp name_node.cpp name_node_ins.cpp node_info.cpp server.cpp \
server_ins.cpp tracker.cpp worker.cpp worker_ins.cpp

OBJ = bus.o name_node.o name_node_ins.o node_info.o server.o \
server_ins.o tracker.o worker.o worker_ins.o

EXE = name_node_ins server_ins worker_ins

PROTOC = protoc -I=./ --cpp_out=./ 

all: ${EXE}

bus.o: bus.cpp commom.h node.h tracker.h message.h
	${CC} ${CFLAGS} ${INCLUDE_PATH} -c bus.cpp

name_node.o: name_node.cpp commom.h node.h tracker.h message.h
	${CC} ${CFLAGS} ${INCLUDE_PATH} -c bus.cpp

${EXE}: %: %.o worker.o message_header.pb.o node_info.o
	${CC} ${LDFLAGS} -o $@ $< worker.o message_header.pb.o \
	node_info.o

node_info.o: node_info.cpp common.h
	${CC} ${CFLAGS} ${INCLUDE_PATH} -c node_info.cpp

worker.o: worker.cpp common.h node.h message_header.pb.h
	${CC} ${CFLAGS} ${INCLUDE_PATH} -c worker.cpp

main.o: main.cpp common.h node.h
	${CC} ${CFLAGS} ${INCLUDE_PATH} -c main.cpp

message_header.pb.o: message_header.pb.cc message_header.pb.h
	${CC} ${CFLAGS} ${INCLUDE_PATH} -c message_header.pb.cc

message_header.pb.h: message_header.proto
	${PROTOC} message_header.proto

clean:
	rm -rf *.o

.PHONY: clean
