#include "Map.h"

Map::Map(int w, int h) {
	this->h = h;
	this->w = w;
	this->cityCount = 0;
	this->numberOfRealCities = 0;
	
	map = new char* [h];
	cities = new City** [h];
	for (int i = 0; i < h; i++) {
		map[i] = new char[w];
		cities[i] = new City* [w];
		for (int j = 0; j < w; j++) {
			cities[i][j] = nullptr;
		}
	}
}

void Map::read() {
	char c;
	for (int i = 0; i < h; i++) {
		for (int j = 0; j < w; j++) {
			c = getchar();
			if (c == '\n') {
				j--;
				continue;
			}
			map[i][j] = c;
		}
	}
}

void Map::readFlights(int howMany) {
	int firstHashIndex, secondHashIndex, flightDuration;
	MyString firstCityName, secondCityName;
	City* firstCity;
	City* secondCity;

	for (int i = 0; i < howMany; i++) {
		cin >> firstCityName >> secondCityName >> flightDuration;
		firstHashIndex = getIndexFromCityName(firstCityName);
		secondHashIndex = getIndexFromCityName(secondCityName);
		firstCity = this->hashmap[firstHashIndex].searchForCity(firstCityName);
		secondCity = this->hashmap[secondHashIndex].searchForCity(secondCityName);
		if (firstCity != nullptr && secondCity != nullptr) {
			firstCity->neighbourList->addConnection(secondCity, flightDuration);
			continue;
		}
	}
}

void Map::print() {
	cout << "\n\n\t\t\tmap\n";
	for (int i = 0; i < h; i++) {
		for (int j = 0; j < w; j++) {
			cout << map[i][j];
		}
		cout << '\n';
	}
	cout << "\t\t\t~map\n\n";
}

void Map::printCitiesNames() {
	int counter = 1;
	for (int i = 0; i < h; i++) {
		for (int j = 0; j < w; j++) {
			if (cities[i][j] != nullptr) {
				cout << counter++ << ". " << cities[i][j]->name << '\n';
				//cout << "x: " << j << " y: " << i << "\n\n"; //coordinates, uncomment to get this
			}
		}
	}
}

void Map::printCityInfoAndNeighbours() {
	for (int i = 0; i < h; i++) {
		for (int j = 0; j < w; j++) {
			if (cities[i][j] != nullptr) {
				cout << "\n\n---------------------------";
				cout << "\ny: " << i << " x: " << j << "\nNAME: -" << cities[i][j]->name << '\n';
				cout << "connections number: " << cities[i][j]->neighbourList->numberOfConnections << '\n';
				cities[i][j]->neighbourList->printList();
			}
		}
	}
}

void Map::countCitiesAndCreateArr() {
	for (int i = 0; i < h; i++) {
		for (int j = 0; j < w; j++) {
			if (map[i][j] == CITY_SIGN) {
				cityCount++;
				numberOfRealCities++;
			}
		}
	}
	processCities();
}

void Map::findRoadsFromCities() {
	char curr;
	for (int i = 0; i < h; i++) {
		for (int j = 0; j < w; j++) {
			if (cities[i][j] != nullptr) {
				//lower
				if (i > 0) {
					curr = map[i - 1][j];
					if (curr == ROAD_SIGN) {
						findNeighbour(i, j, i - 1, j);
					}
					if (curr == CITY_SIGN) {
						cities[i][j]->neighbourList->addConnection(cities[i - 1][j], 1);
					}
				}
				//upper
				if (i < h - 1) {
					curr = map[i + 1][j];
					if (curr == ROAD_SIGN) {
						findNeighbour(i, j, i + 1, j);
					}
					if (curr == CITY_SIGN) {
						cities[i][j]->neighbourList->addConnection(cities[i + 1][j], 1);
					}
				}
				//left
				if (j > 0) {
					curr = map[i][j - 1];
					if (curr == ROAD_SIGN) {
						findNeighbour(i, j, i, j - 1);
					}
					if (curr == CITY_SIGN) {
						cities[i][j]->neighbourList->addConnection(cities[i][j - 1], 1);
					}
				}
				//right
				if (j < w - 1) {
					curr = map[i][j + 1];
					if (curr == ROAD_SIGN) {
						findNeighbour(i, j, i, j + 1);
					}
					if (curr == CITY_SIGN) {
						cities[i][j]->neighbourList->addConnection(cities[i][j + 1], 1);
					}
				}
			}
		}
	}
}

unsigned long Map::getIndexFromCityName(MyString name) { //hash function	http://www.cse.yorku.ca/~oz/hash.html
	unsigned char* temp = (unsigned char*)name.str;
	int i;
	unsigned long hash = 6721;
	while (i = *temp++) {
		hash = ((hash << 5) + hash) + i;
	}
	return (hash % HASHMAP_SIZE);
}


void Map::createHashMap() {
	for (int i = 0; i < h; i++) {
		for (int j = 0; j < w; j++) {
			if (cities[i][j] != nullptr) {
				hashmap[getIndexFromCityName(cities[i][j]->name)].addConnection(cities[i][j], 0);
			}
		}
	}
}

void Map::printHashMap() {
	int cntr = 1;
	for (int i = 0; i < HASHMAP_SIZE; i++) {
		if (hashmap[i].head != nullptr) {
			cout << cntr++ << ". \n";
			hashmap[i].printList();
		}	
	}
}

void Map::markCrossRoads() {
	int roadsNeighbouring;
	int maxH = h - 1;
	int maxW = w - 1;
	for (int i = 0; i < h; i++) {
		for (int j = 0; j < w; j++) {
			if (j == 8) {
				int x;
				x = 0;
			}
			if (map[i][j] == ROAD_SIGN) {	
				roadsNeighbouring = 0; // if roadsNeighbouring reach 3 or 4, it will be the crossroad
				if (i > 0) { //check upper square
					if (map[i - 1][j] == ROAD_SIGN || map[i - 1][j] == CITY_SIGN) {
						roadsNeighbouring++;
					}
				}
				if (i < maxH) { //check bottom square
					if (map[i + 1][j] == ROAD_SIGN || map[i + 1][j] == CITY_SIGN) {
						roadsNeighbouring++;
					}
				}
				if (!roadsNeighbouring) {
					continue; //because there will no more than 2 roads
				}
				if (j > 0) { //check left square
					if (map[i][j - 1] == ROAD_SIGN || map[i][j - 1] == CITY_SIGN) {
						roadsNeighbouring++;
					}
				}
				if (j < maxW) { //check right square
					if (map[i][j + 1] == ROAD_SIGN || map[i][j + 1] == CITY_SIGN) {
						roadsNeighbouring++;
					}
				}
				if (roadsNeighbouring > 2) {
					map[i][j] = CITY_SIGN;
					cities[i][j] = new City;
					this->cityCount++;
				}
			}
		}
	}
}

void Map::findNeighbour(int lastY, int lastX, int currentY, int currentX) {
	//lastXY is city possition		currentXY is first # position
	int mainCityY = lastY;
	int mainCityX = lastX;
	int length = 1;
	// serach for next # return true if * is met		or false if road is over
	char curr;
	for (;;) {
		//upper
		if (currentY > 0 && currentY - 1 != lastY) {
			curr = map[currentY - 1][currentX];
			if (curr == ROAD_SIGN) {
				lastY = currentY;
				lastX = currentX;
				currentY--;
				length++;
				continue;
			}
			if (curr == CITY_SIGN) {
				length++;
				cities[mainCityY][mainCityX]->neighbourList->addConnection(cities[currentY - 1][currentX], length);
				return;
			}
		}
		//lower
		if (currentY < h - 1 && currentY + 1 != lastY) {
			curr = map[currentY + 1][currentX];
			if (curr == ROAD_SIGN) {
				lastY = currentY;
				lastX = currentX;
				currentY++;
				length++;
				continue;
			}
			if (curr == CITY_SIGN) {
				length++;
				cities[mainCityY][mainCityX]->neighbourList->addConnection(cities[currentY + 1][currentX], length);
				return;
			}
		}
		//left
		if (currentX > 0 && currentX - 1 != lastX) {
			curr = map[currentY][currentX - 1];
			if (curr == ROAD_SIGN) {
				lastX = currentX;
				lastY = currentY;
				currentX--;
				length++;
				continue;
			}
			if (curr == CITY_SIGN) {
				length++;
				cities[mainCityY][mainCityX]->neighbourList->addConnection(cities[currentY][currentX - 1], length);
				return;
			}
		}
		//right
		if (currentX < w - 1 && currentX + 1 != lastX) {
			curr = map[currentY][currentX + 1];
			if (curr == ROAD_SIGN) {
				lastX = currentX;
				lastY = currentY;
				currentX++;
				length++;
				continue;
			}
			if (curr == CITY_SIGN) {
				length++;
				cities[mainCityY][mainCityX]->neighbourList->addConnection(cities[currentY][currentX + 1], length);
				return;
			}
		}
		return;
	}
}

void Map::processCities() {
	/*
	[y-1 x-1]	[y-1   x]	[y-1 x+1]


	[y   x-1]	[   *   ]	[y   x+1]


	[y+1 x-1]	[y+1   x]	[y+1 x+1]
	*/
	for (int y = 0; y < h; y++) {
		for (int x = 0; x < w; x++) {
			if (map[y][x] == CITY_SIGN) {
				cities[y][x] = new City;
				if (y - 1 >= 0) { //upper row
					if (x - 1 >= 0) {
						if (map[y - 1][x - 1] >= '0') {
							cities[y][x]->name = readName(map, y - 1, x - 1, w);
							continue;
						}
					}
					if (x + 1 <= w) {
						if (map[y - 1][x + 1] >= '0') {
							cities[y][x]->name = readName(map, y - 1, x + 1, w);
							continue;
						}
					}
					if (map[y - 1][x] >= '0') {
						cities[y][x]->name = readName(map, y - 1, x, w);
						continue;
					}
				}
				if (x - 1 >= 0) {
					if (map[y][x - 1] >= '0') {
						cities[y][x]->name = readName(map, y, x - 1, w);
						continue;

					}
				}
				if (x + 1 <= w) {
					if (map[y][x + 1] >= '0') {
						cities[y][x]->name = readName(map, y, x + 1, w);
						continue;

					}

				}
				if (y + 1 <= h) {
					if (x - 1 >= 0) {
						if (map[y + 1][x - 1] >= '0') {
							cities[y][x]->name = readName(map, y + 1, x - 1, w);
							continue;

						}
					}
					if (x + 1 <= w) {
						if (map[y + 1][x + 1] >= '0') {
							cities[y][x]->name = readName(map, y + 1, x + 1, w);
							continue;

						}
					}
					if (map[y + 1][x] >= '0') {
						cities[y][x]->name = readName(map, y + 1, x, w);
						continue;

					}
				}
			}
		}
	}
	createHashMap();
	markCrossRoads();
}

MyString Map::readName(char** map, int y, int x, int sizeX) {
	char buff[BUFFOR_SIZE] = { '\0' };
	char c;
	int tempX = x;
	while (tempX - 1 >= 0 && tempX--) {
		c = map[y][tempX];
		if ((c > 'Z' || c < 'A') && (c > '9' || c < '0')) {
			tempX++;
			break;
		} //we have start;
	}

	int helper = 0;
	for (int i = tempX; i < sizeX; i++) {

		c = map[y][tempX];
		if ((c > 'Z' || c < 'A') && (c > '9' || c < '0')) {
			break;
		}
		buff[helper] = c;
		helper++;
		map[y][tempX] = '.';
		tempX++;
	}
	MyString s(buff);
	return s;
}

Map::~Map() {
	for (int i = 0; i < h; i++) {
		delete[] map[i];
		delete[] cities[i];
	}
	delete[] map;
	delete[] cities;
}