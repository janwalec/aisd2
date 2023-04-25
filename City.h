#pragma once
#include "MyString.h"
struct City {
public:
	MyString name;
	int cityType; //-1 free;	0 crossroad;	1 real city with name
	City();
	//List neighbours
};

