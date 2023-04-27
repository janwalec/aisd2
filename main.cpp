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

int main() {
	int w, h;
	cin >> w >> h;
	Map map(w, h);
	map.read();
	map.countCitiesAndCreateArr();
	map.findRoadsFromCities();
	//map.print();
	//map.printCitiesNames();
	map.printCityInfoAndNeighbours();
	return 0;
}