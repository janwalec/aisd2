#include "Heap.h"

int main() {
	int w, h;
	cin >> w >> h;
	Map map(w, h);
	map.read();
	map.countCitiesAndCreateArr();
	map.findRoadsFromCities();
	int flights, howManyCommands;
	cin >> flights;
	if (flights) {
		map.readFlights(flights);
	}
	
	cin >> howManyCommands;
	MyString rootName, targetName;
	int rootHashedIndex, targetHashedIndex;
	int rootHeapIndex, targetHeapIndex;
	bool questionType;
	Heap heap(&map, map.cityCount);
	for (int i = 0; i < howManyCommands; i++) {
		cin >> rootName >> targetName >> questionType;
		rootHashedIndex = map.getIndexFromCityName(rootName);
		targetHashedIndex = map.getIndexFromCityName(targetName);
		rootHeapIndex = map.hashmap[rootHashedIndex].searchForCity(rootName)->heapIndex;
		targetHeapIndex = map.hashmap[targetHashedIndex].searchForCity(targetName)->heapIndex;
		heap.setRoot(rootHeapIndex);
		heap.printHeap();
		
		/*heap.resetHeap();
		cout << "\n\n\n\n\n\n";
		*/
	}

	
	return 0;
}