#pragma once
#include "ConnectionNode.h"
struct City;
class ConnectionNode;

class ConnectionList {
public:
	ConnectionNode* head;
	int numberOfConnections;
	ConnectionList();
	~ConnectionList();
	void addConnection(City* city, int road);
	void printList();
};