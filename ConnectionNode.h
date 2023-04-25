#pragma once
#include "City.h"
class ConnectionNode {
public:
	City* city;
	ConnectionNode* next;
	int road;
	ConnectionNode(City* c, int r);
};

