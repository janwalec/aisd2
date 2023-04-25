#pragma once
#include "ConnectionNode.h"
class ConnectionList {
public:
	ConnectionNode* head;
	int numberOfConnections;
	ConnectionList();
	~ConnectionList();
	void addConnection(City* city, int road);
};