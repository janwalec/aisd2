#pragma once
#define LARGE_NUM 9999999999999
#include "MyString.h"
#include "ConnectionList.h"
class ConnectionList;
class ConnectionNode;

struct City {
public:
	MyString name;
	int distance;
	int heapIndex;
	City* previous;
	ConnectionList* neighbourList;
	City();
	~City();
};