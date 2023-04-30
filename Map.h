#pragma once
#define BUFFOR_SIZE 100
#define HASHMAP_SIZE 2121
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
	ConnectionList hashmap[HASHMAP_SIZE];
	int h, w, cityCount;
	Map(int w, int h);
	void read();
	void readFlights(int howMany);
	void countCitiesAndCreateArr();
	void findRoadsFromCities();
	void createHashMap();
	unsigned long getIndexFromCityName(MyString name);
	~Map();
	
	//visualisation
	void print();
	void printCitiesNames();
	void printCityInfoAndNeighbours();
	void printHashMap();
};