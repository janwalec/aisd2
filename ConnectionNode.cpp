#include "ConnectionNode.h"

ConnectionNode::ConnectionNode(City* c, int r) {
	this->city = c;
	this->road = r;
	this->next = nullptr;
}
