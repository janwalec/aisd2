#include "City.h"

City::City() {
	MyString noName;
	neighbourList = new ConnectionList;
	this->heapPriority = LARGE_NUM;
	this->heapIndex = -100; //random minus number
	this->name = noName;
}

City::~City() {
	delete neighbourList;
}
