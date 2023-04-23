
#include "Map.h"

int main() {
	int w, h;
	cin >> w >> h;
	Map map(w, h);
	map.read();
	map.countCitiesAndCreateArr();
	//map.printCitiesList();
	map.print();
	

	return 0;
}

