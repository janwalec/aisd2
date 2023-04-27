#define SIZE 4321
#include "Map.h"

unsigned long getIndexFromCityName(MyString name) { //hash function	http://www.cse.yorku.ca/~oz/hash.html
	unsigned char* temp = (unsigned char*)name.str;
	int i;
	unsigned long hash = 6721;
	while (i = *temp++) {
		hash = ((hash << 5) + hash) + i;
	}
	return (hash % SIZE);
}

bool findNeighbour(int lastY, int lastX, int currentY, int currentX, Map& map);

int main() {
	int w, h;
	cin >> w >> h;
	Map map(w, h);
	map.read();
	map.countCitiesAndCreateArr();
	
	char curr;
	for (int i = 0; i < h; i++) {
		for (int j = 0; j < w; j++) {
			if (map.cities[i][j] != nullptr) {
				//lower
				if (i > 0) {
					curr = map.map[i - 1][j];
					if (curr == '#') {
						if (findNeighbour(i, j, i - 1, j, map)) {
							map.cities[i][j]->neighbourList->numberOfConnections++;
							continue;
						}
					}
					if (curr == '*') {
						map.cities[i][j]->neighbourList->addConnection(map.cities[i - 1][j], 1);
						continue;
					}
				}
				//upper
				if (i < h - 1) {
					curr = map.map[i + 1][j];
					if (curr == '#') {
						if (findNeighbour(i, j, i + 1, j, map)) {
							map.cities[i][j]->neighbourList->numberOfConnections++;
							continue;
						}
					}
					if (curr == '*') {
						map.cities[i][j]->neighbourList->addConnection(map.cities[i + 1][j], 1);
						continue;
					}
				}
				//left
				if (j > 0) {
					curr = map.map[i][j - 1];
					if (curr == '#') {
						if (findNeighbour(i, j, i, j - 1, map)) {
							map.cities[i][j]->neighbourList->numberOfConnections++;
							continue;
						}
					}
					if (curr == '*') {
						map.cities[i][j]->neighbourList->addConnection(map.cities[i][j - 1], 1);
						continue;
					}
				}
				//right
				if (j < w - 1) {
					curr = map.map[i][j + 1];
					if (curr == '#') {
						if (findNeighbour(i, j, i, j + 1, map)) {
							map.cities[i][j]->neighbourList->numberOfConnections++;
							continue;
						}
					}
					if (curr == '*') {
						map.cities[i][j]->neighbourList->addConnection(map.cities[i][j + 1], 1);
						continue;
					}
				}
			}
		}
	}

	//map.print();
	//map.printCitiesNames();
	for (int i = 0; i < h; i++) {
		for (int j = 0; j < w; j++) {
			if (map.cities[i][j] != nullptr) {
				cout << "\n\nNAME: " << map.cities[i][j]->name << '\n';
				map.cities[i][j]->neighbourList->printList();
			}
		}
	}
	return 0;
}

bool findNeighbour(int lastY, int lastX, int currentY, int currentX, Map& map) {
	//lastXY is city possition		currentXY is first # position
	int mainCityY = lastY;
	int mainCityX = lastX;
	int w = map.w;
	int h = map.h;
	int length = 0;
	// serach for next # return true if * is met		or false if road is over
	for (;;) { 
		//upper
		if (currentY - 1 > 0 && currentY - 1 != lastY) { 
			if (map.map[currentY - 1][currentX] == '#') {
				length++;
				lastY = currentY - 1;
				continue;
			}
			if (map.map[currentY - 1][currentX] == '*') {
				length++;
				map.cities[mainCityY][mainCityX]->neighbourList->addConnection(map.cities[currentY - 1][currentX], length);
				return true;
			}
		}
		//lower
		if (currentY + 1 < h - 1 && currentY + 1 != lastY) {
			if (map.map[currentY + 1][currentX] == '#') {
				length++;
				lastY = currentY + 1;
				continue;
			}
			if (map.map[currentY + 1][currentX] == '*') {
				length++;
				map.cities[mainCityY][mainCityX]->neighbourList->addConnection(map.cities[currentY + 1][currentX], length);
				return true;
			}
		}
		//left
		if (currentX - 1 > 0 && currentX - 1 != lastX) {
			if (map.map[currentY][currentX - 1] == '#') {
				length++;
				lastX = currentX - 1;
				continue;
			}
			if (map.map[currentY][currentX - 1] == '*') {
				length++;
				map.cities[mainCityY][mainCityX]->neighbourList->addConnection(map.cities[currentY][currentX - 1], length);
				return true;
			}
		}
		//right
		if (currentX + 1 < w - 1 && currentX + 1 != lastX) {
			if (map.map[currentY][currentX + 1] == '#') {
				length++;
				lastX = currentX + 1;
				continue;
			}
			if (map.map[currentY][currentX + 1] == '*') {
				length++;
				map.cities[mainCityY][mainCityX]->neighbourList->addConnection(map.cities[currentY][currentX + 1], length);
				return true;
			}
		}
		return false;
	}
}