#pragma once
#define BUFFOR_SIZE 100
#include <iostream>
#include "MyString.h"
using std::cin;
using std::cout;

class Map {
	void processCities();
	MyString readName(char** map, int y, int x, int sizeX);
public:
	MyString* citiesName;
	char** map;
	int h, w, cityCount;
	Map(int w, int h);
	void read();
	void print();
	void countCitiesAndCreateArr();
	void printCitiesList();
	~Map();
};




