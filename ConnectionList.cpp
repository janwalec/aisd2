#include "ConnectionList.h"

ConnectionList::ConnectionList() {
	this->head = nullptr;
	this->numberOfConnections = 0;
}

ConnectionList::~ConnectionList() {
	ConnectionNode* prev;
	while (head != nullptr) {
		prev = head;
		head = head->next;
		delete prev;
	}
}

City* ConnectionList::searchForCity(MyString n) {
	ConnectionNode* temp = head;
	while (temp != nullptr) {
		if (temp->city->name.length == n.length) {
			if (temp->city->name == n) {
				return temp->city;
			}
		}
		temp = temp->next;
	}
	return nullptr;
}

void ConnectionList::addConnection(City* city, int road) {
	ConnectionNode* newConnection = new ConnectionNode(city, road);
	if (head == nullptr) {
		this->head = newConnection;
		numberOfConnections++;
		return;
	}
	ConnectionNode* temp = head;
	while (temp->next != nullptr) {
		temp = temp->next;
	}
	temp->next = newConnection;
	numberOfConnections++;
}

void ConnectionList::printList() {
	ConnectionNode* temp = head;
	while (temp != nullptr) {
		cout << temp->city->name << "_ distance: " << temp->road << '\n';
		temp = temp->next;
	}
}
