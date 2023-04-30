#pragma once
#include "Map.h"
class Heap {
private:
	void swap(City** first, City** second);
public:
	int size;
	int originalSize;
	City** array;
	Map* map;
	Heap(Map* map, int size);
	void resetHeap();
	~Heap();
	int leftChild(int n);
	int rightChild(int n);
	int parent(int n);
	void pushUp(int index);
	void pushDown(int index);
	City* pop();
	void setRoot(int index);

	//visualisation
	void printHeap();
};

