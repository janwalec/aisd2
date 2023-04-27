#pragma once
#include "MyString.h"
#include "ConnectionList.h"
class ConnectionList;
class ConnectionNode;

struct City {
public:
	MyString name;
	ConnectionList* neighbourList;
	City();
	~City();
};