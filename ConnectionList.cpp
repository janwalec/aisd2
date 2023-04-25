#include "ConnectionList.h"

ConnectionList::ConnectionList() {
	this->head = nullptr;
	this->numberOfConnections = 0;
}

ConnectionList::~ConnectionList() {
	if(head != nullptr) {
		ConnectionNode* temp1 = head;
		ConnectionNode* temp2 = temp1;
		while (temp2 != nullptr) {
			temp2 = temp1->next;
			delete temp1;
		}
	}
}

void ConnectionList::addConnection(City* city, int road) {
	ConnectionNode* newConnection = new ConnectionNode(city, road);
	if (head == nullptr) {
		this->head = newConnection;
		numberOfConnections++;
		return;
	}
	ConnectionNode* temp = head;
	while (temp != nullptr) {
		temp = temp->next;
	}
	temp = newConnection;
	temp->next = nullptr;
	numberOfConnections++;
}
