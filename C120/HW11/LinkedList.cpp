# include <iostream>
# include <string>
# include <sstream>
# include "LinkedList.h"
# include "Node.h"

using std::string, std::ostream;

LinkedList::LinkedList() : head(nullptr), tail(nullptr) {}

LinkedList::~LinkedList() {
	clear();
}

LinkedList::LinkedList(const LinkedList& source) : head(nullptr), tail(nullptr) {
	*this = source;
}

LinkedList& LinkedList::operator=(const LinkedList& source) {
	if (this == &source) return *this;

	this->clear();
	Node* sNode = source.head;
	head = new Node(*sNode);
	Node* tNode = head;
	while (sNode != nullptr){
		tNode->next = new Node(*(sNode->next));
		
		tNode = tNode->next;
		sNode = sNode->next;
	}
	tail = tNode;
	return *this;
}

void LinkedList::insert(string location, int year, int month, double temperature) {
	Node* currNode = head;
	Node* newNode = new Node(location, year, month, temperature);

	bool sameHT = false;
	if (tail != nullptr && head == tail) sameHT = true;
	
	if (head == nullptr){
		head = newNode;
		tail = newNode;
		return;
	}
	
	else if (!(*head < *newNode)){
		Node* n = new Node(*head);
		delete head;
		head = newNode;
		newNode->next = n;
		if (sameHT) tail = n;
		currNode = head;
	}

	else while (currNode->next != nullptr){
		if (!(  *(currNode->next) < *(newNode) )){
			Node* tempNode = currNode->next;
			currNode->next = newNode;
			newNode->next = tempNode;
			break;
		}

		currNode = currNode->next;
	}
	if (currNode->next == nullptr) {
		currNode->next = newNode;
		tail = newNode;

	}

}

void LinkedList::clear() {

	Node* currNode = head;
	while (currNode->next != nullptr){
		Node* nextNode = currNode->next;
		delete currNode;
		currNode = nextNode;
	}
	delete currNode;
	head = nullptr;
	tail = nullptr;
}

Node* LinkedList::getHead() const {
	return head;
}

string LinkedList::print() const {

	Node* currNode = head;
	std::stringstream ioSS;
	while (currNode != nullptr){
		TemperatureData& d = currNode->data;
		ioSS << d.id << " "  << d.year <<  " "  << d.month <<  " " << d.temperature << "\n";
		
		currNode = currNode->next;
	}
	return ioSS.str();
}

ostream& operator<<(ostream& os, const LinkedList& ll) {
	string printString = ll.print();
	os << printString;
	return os;
}
