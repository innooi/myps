CC = g++
CFLAGS = -Wall -std=c++11 -O2
LDFLAGS = -lzmq -lglog -lprotobuf -lboost_system -lboost_filesystem -lboost_thread -lyaml-cpp
INCLUDE_PATH = -I./ -I/usr/local/boost_1_58_0/boost

SRC = bus.cpp client.cpp server.cpp

OBJ = bus.o client.o server.o

EXE = client server

PROTOC = protoc -I=./ --cpp_out=./ 

all: ${EXE}

${EXE}: %: %.o bus.o task.pb.o
	${CC} ${LDFLAGS} ${INCLUDE_PATH} -o $@ $< bus.o task.pb.o


task.pb.o: task.pb.cc task.pb.h
	${CC} ${CFLAGS} -c task.pb.cc

bus.o: bus.cpp bus.h common.h task.pb.h
	${CC} ${CFLAGS} -c bus.cpp

client.o: client.cpp common.h task.pb.h
	${CC} ${CFLAGS} -c client.cpp

server.o: server.cpp common.h task.pb.h
	${CC} ${CFLAGS} -c server.cpp

	
task.pb.h: task.proto
	${PROTOC} task.proto

clean:
	rm -rf *.o

.PHONY: clean
	
