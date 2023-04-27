#include "City.h"

City::City() {
	MyString noName;
	neighbourList = new ConnectionList;
	this->name = noName;
}

City::~City() {
	delete neighbourList;
}
