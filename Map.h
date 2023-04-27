#pragma once
#define BUFFOR_SIZE 100
#include <iostream>
#include "ConnectionList.h"
using std::cin;
using std::cout;

class Map {
	void processCities();
	void markCrossRoads();
	MyString readName(char** map, int y, int x, int sizeX);
public:
	City*** cities;
	char** map;
	int h, w, cityCount;
	Map(int w, int h);
	void read();
	void countCitiesAndCreateArr();
	~Map();
	//visualisation
	void print();
	void printCitiesNames();
};