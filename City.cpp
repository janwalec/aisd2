#include "City.h"

City::City() {
	MyString noName;
	neighbourList = new ConnectionList;
	this->distance = LARGE_NUM;
	this->heapIndex = -100; //random minus number
	this->name = noName;
	this->previous = nullptr;
}

City::~City() {
	delete neighbourList;
}
