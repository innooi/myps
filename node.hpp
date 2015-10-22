#pragma once

#include "common.h"
#include "bus.h"

namespace PS{
	enum class NodeType{
		SERVER,
		WORKER,
		NAMENODE
	};

	struct Node {
		NodeId id;
		std::string ip;
		int port;
		NodeType nodeType;
	};

	struct MyNode{
		NodeId id;
		std::string ip;
		int port;
		NodeType nodeType;
		std::vector<Node> serverList;
		std::vector<Node> workerList;
		std::vector<Node> nameNodeList;
		Bus *comm;

		void Init(NodeId myID, std::string myIP, int myPort) {
			serverList.clear();
			workerList.clear();
			nameNodeList.clear();
			this->id = myID;
			this->ip = myIP;
			this->port = myPort;
			comm = new Bus();
			comm->Init(myID);

			/*
			连接yaml文件中的节点，成功后加入到本地的信息
			*/

			YAML::Node config = YAML::LoadFile("node_list.yaml");
			for (auto it = config["NodeList"].begin(); 
				it != config["NodeList"].end();
				++it){
				Node remoteNode;
				remoteNode.id = (*it)["ID"].as<std::string>();
				remoteNode.ip = (*it)["IP"].as<std::string>();
				remoteNode.port = (*it)["PORT"].as<int>();
				string strType = (*it)["TYPE"].as<std::string>();
				if ("Worker" == strType) {
					remoteNode.nodeType = WORKER;
					if (true == comm->Connect(remoteNode)) {
						workerList.push_back(remoteNode);
					}
				}
				else if ("Server" == strType) {
					remoteNode.nodeType = SERVER;
					if (true == comm->Connect(remoteNode)) {
						serverList.push_back(remoteNode);
					}
				}
				else if ("NameNode" == strType) {
					remoteNode.nodeType = NAMENODE;
					if (true == comm->Connect(remoteNode)) {
						nameNodeList.push_back(remoteNode);
					}
				}				
			}
		}
	};
}
