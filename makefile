CC = g++
CFLAGS = -Wall -std=c++11 -O2

LDFLAGS = -L/usr/local/lib -lzmq -lglog -lprotobuf -lboost_system \
-lboost_filesystem -lboost_thread -lboost_serialization -lyaml-cpp

INCLUDE_PATH = -I./ -I/usr/local/boost_1_58_0/boost \
-I/usr/local/include

SRC = worker.cpp main.cpp node_info.cpp

OBJ = worker.o main.o node_info.o

EXE = main

PROTOC = protoc -I=./ --cpp_out=./ 

all: ${EXE}

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
