#include "Heap.h"

Heap::Heap(Map* map, int size) {
	this->map = map;
	array = new City* [size];
	int counter = 0;
	for (int i = 0; i < map->h; i++) {
		for (int j = 0; j < map->w; j++) {
			if (map->cities[i][j] != nullptr) {
				array[counter]= map->cities[i][j];
				map->cities[i][j]->heapIndex = counter++;
			}
		}
	}
	this->size = counter;
	this->originalSize = counter;
}

void Heap::resetHeap() {
	this->size = originalSize;
	for (int i = 0; i < originalSize; i++) {
		array[i]->heapPriority = LARGE_NUM;
		array[i]->heapIndex = i;
	}
}

Heap::~Heap() {
	delete[] array;
}

int Heap::leftChild(int n) {
	int index = 2 * n + 1;
	if (index < size) {
		return -1;
	}
	return index;
}

int Heap::rightChild(int n) {
	int index = 2 * n + 2;
	if (index < size) {
		return -1;
	}
	return index;
}

int Heap::parent(int n) {
	if (n < size) {
		return -1;
	}
	return n;
}

void Heap::swap(City** first, City** second) {
	City* temp = *first;
	int firstID = (*first)->heapIndex;
	int secondID = (*second)->heapIndex;
	*first = *second;
	*second = temp;
	(*first)->heapIndex = firstID;
	(*second)->heapIndex = secondID;
}

void Heap::pushUp(int index) {
	while (parent(index) >= 0) {
		if (array[index]->heapPriority < array[parent(index)]->heapPriority) {
			swap(&array[parent(index)], &array[index]);
			index = parent(index);
			continue;
		}
		break; //if not less
	}
}

void Heap::pushDown(int index) {
	int rightChildIndex;
	int leftChildIndex;
	for (;;) {
		rightChildIndex = rightChild(index);
		leftChildIndex = leftChild(index);
		//if both exist
		if (rightChildIndex >= 0 && leftChildIndex >= 0) { 
			if (array[leftChildIndex]->heapPriority < array[index]->heapPriority && array[rightChildIndex]->heapPriority < array[index]->heapPriority){
				if (array[leftChildIndex]->heapPriority < array[rightChildIndex]->heapPriority) { //swap left if it's less than right child
					swap(&array[index], &array[leftChildIndex]);
					index = leftChildIndex;
				} else { //swap right
					swap(&array[index], &array[rightChildIndex]);
					index = rightChildIndex;
				}
				continue;
			}	
		}
		if (leftChildIndex >= 0 && array[leftChildIndex]->heapPriority < array[index]->heapPriority) { //only left is less than parent
			swap(&array[index], &array[leftChildIndex]);
			index = leftChildIndex;
			continue;
		}
		if (rightChildIndex >= 0 && array[rightChildIndex]->heapPriority < array[index]->heapPriority) { //only right is less than parent
			swap(&array[index], &array[rightChildIndex]);
			index = rightChildIndex;
			continue;
		}
		break; //none fits and heap is okay		
	}
}

City* Heap::pop() {
	City* pooper = array[0];
	swap(&array[0], &array[size - 1]);
	size = size - 1;
	pushDown(0);
	return pooper;
}

void Heap::setRoot(int index) {
	array[index]->heapPriority = 0;
	swap(&array[0], &array[index]);
	pushUp(index);
}

void Heap::printHeap() {
	for (int i = 0; i < this->size; i++) {
		cout << array[i]->name << " index: " << array[i]->heapIndex << endl;
		cout << "---\n";
	}
}