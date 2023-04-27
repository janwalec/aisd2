#pragma once
#define BUFFOR_SIZE 100
#define CITY_SIGN '*'
#define ROAD_SIGN '#'
#include "ConnectionList.h"

class Map {
	void processCities();
	void markCrossRoads();
	void findNeighbour(int lastY, int lastX, int currentY, int currentX);
	MyString readName(char** map, int y, int x, int sizeX);
public:
	City*** cities;
	char** map;
	int h, w, cityCount;
	Map(int w, int h);
	void read();
	void countCitiesAndCreateArr();
	void findRoadsFromCities();
	~Map();
	
	//visualisation
	void print();
	void printCitiesNames();
	void printCityInfoAndNeighbours();
};