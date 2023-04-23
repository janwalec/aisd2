#include "Map.h"

Map::Map(int w, int h) {
	this->h = h;
	this->w = w;
	this->cityCount = 0;
	this->citiesName = nullptr;
	map = new char* [h];
	for (int i = 0; i < h; i++) {
		map[i] = new char[w];
	}
}

void Map::read() {
	for (int i = 0; i < h; i++) {
		for (int j = 0; j < w; j++) {
			cin >> map[i][j];
		}
	}
}

void Map::print() {
	cout << "\nmap\n\n";
	for (int i = 0; i < h; i++) {
		for (int j = 0; j < w; j++) {
			cout << map[i][j];
		}
		cout << '\n';
	}
	cout << "\n~map\n";
}

void Map::countCitiesAndCreateArr() {
	for (int i = 0; i < h; i++) {
		for (int j = 0; j < w; j++) {
			if (map[i][j] == '*') {
				cityCount++;
			}
		}
	}
	citiesName = new MyString[cityCount];
	processCities();
}

void Map::printCitiesList() {
	for (int i = 0; i < cityCount; i++) {
		cout << i + 1 << ". " << citiesName[i] << '\n';
	}
	cout << "cities counter: " << cityCount << '\n';
}

void Map::processCities() {
	/*

	[y-1 x-1]	[y-1   x]	[y-1 x+1]


	[y   x-1]	[   *   ]	[y   x+1]


	[y+1 x-1]	[y+1   x]	[y+1 x+1]

	*/
	char curr;
	int whichCity = 0;
	for (int y = 0; y < h; y++) {
		for (int x = 0; x < w; x++) {
			if (map[y][x] == '*') {
				if (y - 1 >= 0) { //upper row
					if (x - 1 >= 0) {
						curr = map[y - 1][x - 1];
						if ((curr >= 'A' && curr <= 'Z') || (curr >= '0' && curr <= '9')) {
							citiesName[whichCity] = readName(map, y - 1, x - 1, w);
							whichCity++;
							continue;
						}
					}
					if (x + 1 <= w) {
						curr = map[y - 1][x + 1];
						if ((curr >= 'A' && curr <= 'Z') || (curr >= '0' && curr <= '9')) {
							citiesName[whichCity] = readName(map, y - 1, x + 1, w);
							whichCity++;
							continue;
						}
					}
					curr = map[y - 1][x];
					if ((curr >= 'A' && curr <= 'Z') || (curr >= '0' && curr <= '9')) {
						citiesName[whichCity] = readName(map, y - 1, x, w);
						whichCity++;
						continue;
					}


				}
				if (x - 1 >= 0) {
					curr = map[y][x - 1];
					if ((curr >= 'A' && curr <= 'Z') || (curr >= '0' && curr <= '9')) {
						citiesName[whichCity] = readName(map, y, x - 1, w);
						whichCity++;
						continue;

					}
				}
				if (x + 1 <= w) {
					curr = map[y][x + 1];
					if ((curr >= 'A' && curr <= 'Z') || (curr >= '0' && curr <= '9')) {
						citiesName[whichCity] = readName(map, y, x + 1, w);
						whichCity++;
						continue;

					}

				}
				if (y + 1 <= h) {
					if (x - 1 >= 0) {
						curr = map[y + 1][x - 1];
						if ((curr >= 'A' && curr <= 'Z') || (curr >= '0' && curr <= '9')) {
							citiesName[whichCity] = readName(map, y + 1, x - 1, w);
							whichCity++;
							continue;

						}
					}
					if (x + 1 <= w) {
						curr = map[y + 1][x + 1];
						if ((curr >= 'A' && curr <= 'Z') || (curr >= '0' && curr <= '9')) {
							citiesName[whichCity] = readName(map, y + 1, x + 1, w);
							whichCity++;
							continue;

						}
					}
					curr = map[y + 1][x];
					if ((curr >= 'A' && curr <= 'Z') || (curr >= '0' && curr <= '9')) {
						citiesName[whichCity] = readName(map, y + 1, x, w);
						whichCity++;
						continue;

					}
				}
			}
		}
	}
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
	}
	delete[] map;
	delete[] citiesName;
}
