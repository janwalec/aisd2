#include "Heap.h"
using std::cout;
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
	
	Heap heap(&map, map.cityCount);
	cin >> howManyCommands;
	MyString rootName, targetName;
	int rootHashedIndex, targetHashedIndex;
	City* root;
	City* target;
	bool questionType;

	//map.printCityInfoAndNeighbours();
	City** printer = new City * [map.numberOfRealCities];
	City* marker;
	int cntr;

	for (int i = 0; i < howManyCommands; i++) {
		cin >> rootName >> targetName >> questionType;
		rootHashedIndex = map.getIndexFromCityName(rootName);
		targetHashedIndex = map.getIndexFromCityName(targetName);
		root = map.hashmap[rootHashedIndex].searchForCity(rootName);
		target = map.hashmap[targetHashedIndex].searchForCity(targetName);
		heap.search(root, target);
		//heap.printHeap();
		
		
		if (questionType) {
			cout << target->distance;
			cntr = 0;
			marker = target;
			while (marker != root) {
				if (marker->name.length == 0) {
					marker = marker->previous;
					continue;
				}
				printer[cntr] = marker;
				marker = marker->previous;
				if (marker == nullptr) {
					break;
				}
				cntr++;
			}
			for (int x = cntr - 1; x > 0; x--) {
				cout << " " << printer[x]->name;
			}
		}
		else {
			cout << target->distance;
		}
		cout << '\n';
		
	}
	/*heap.setDistance(2, 20);
	heap.setDistance(0, 19);
	heap.setDistance(5, 26);
	heap.setDistance(7, 2);
	heap.pop();
	heap.pop();*/

	//heap.printHeap();
	
	delete[] printer;
	return 0;
}