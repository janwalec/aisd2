#pragma once
#include "City.h"

struct City;
class ConnectionList;

class ConnectionNode {
public:
	City* city;
	ConnectionNode* next;
	int road;
	ConnectionNode(City* c, int r);
};