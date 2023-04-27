#include "Map.h"

Map::Map(int w, int h) {
	this->h = h;
	this->w = w;
	this->cityCount = 0;
	
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

void Map::countCitiesAndCreateArr() {
	for (int i = 0; i < h; i++) {
		for (int j = 0; j < w; j++) {
			if (map[i][j] == '*') {
				cityCount++;
			}
		}
	}
	processCities();
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
			if (map[i][j] == '#') {	
				roadsNeighbouring = 0; // if roadsNeighbouring reach 3 or 4, it will be the crossroad
				if (i > 0) { //check upper square
					if (map[i - 1][j] == '#' || map[i - 1][j] == '*') {
						roadsNeighbouring++;
					}
				}
				if (i < maxH) { //check bottom square
					if (map[i + 1][j] == '#' || map[i + 1][j] == '*') {
						roadsNeighbouring++;
					}
				}
				if (!roadsNeighbouring) {
					continue; //because there will no more than 2 roads
				}
				if (j > 0) { //check left square
					if (map[i][j - 1] == '#' || map[i][j - 1] == '*') {
						roadsNeighbouring++;
					}
				}
				if (j < maxW) { //check right square
					if (map[i][j + 1] == '#' || map[i][j + 1] == '*') {
						roadsNeighbouring++;
					}
				}
				if (roadsNeighbouring > 2) {
					map[i][j] = '*';
					cities[i][j] = new City;
				}
			}
		}
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
			if (map[y][x] == '*') {
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