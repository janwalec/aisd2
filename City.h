#pragma once
#define LARGE_NUM 99999999999
#include "MyString.h"
#include "ConnectionList.h"
class ConnectionList;
class ConnectionNode;

struct City {
public:
	MyString name;
	int heapPriority;
	int heapIndex;
	ConnectionList* neighbourList;
	City();
	~City();
};