# include <string>
# include "Node.h"

using std::string;

Node::Node() : data(), next(nullptr) {}

Node::Node(string id, int year, int month, double temperature) :
	data(id, year, month, temperature),
	next(nullptr) {}

bool Node::operator<(const Node& b) {	
	return this->data < b.data;
}

Node& Node::operator=(const Node& rhs){
	this->data = rhs.data;
	this->next = rhs.next;
	return *this;
}

Node::Node(const Node& nToCopy) : data(), next(nullptr){
	*this = nToCopy;
}
