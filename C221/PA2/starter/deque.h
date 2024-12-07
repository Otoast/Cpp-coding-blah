#ifndef DEQUE_H
#define DEQUE_H

#include <stdexcept>
#include "node.h"
using namespace std;

template <class Type>
class Deque {
private:
	int s;
	Node<Type>* firstNode;
	Node<Type>* lastNode;

public:
	Deque();
	Deque(const Deque& other); 
	Deque& operator=(const Deque& other); 
	~Deque();
	bool isEmpty();
	int size();
	Type first();
	Type last();
	void insertFirst(Type o);
	void insertLast(Type o);
	Type removeFirst();
	Type removeLast();
};

// Your implementation here 

template <class Type>
Deque<Type>::Deque() :
	firstNode(nullptr),
	lastNode(nullptr),
	s(0) {}

template <class Type>
Deque<Type>::~Deque() {
	Node<Type>* iterNode = firstNode;
	while (iterNode != nullptr){
		Node<Type>* nextNode = iterNode->getNext();
		delete iterNode;
		iterNode = nextNode;
	}
	firstNode = nullptr;
	lastNode = nullptr;
	s = 0;
}

template <class Type>
Deque<Type>::Deque(const Deque& other) {
	this->s = other.s;
	Node<Type>* thisNode = new Node<Type>(other.firstNode->getData());
	this->firstNode = thisNode;

	Node<Type>* otherNode = other.firstNode->getNext();
	while (otherNode != nullptr){
		thisNode->setNext(		new Node<Type>(otherNode->getData())	);
		otherNode = otherNode->getNext();
		Node<Type>* tempNode = thisNode;
		thisNode = thisNode->getNext();
		thisNode->setPrev(tempNode);
		
	}
	lastNode = thisNode;
	lastNode->setNext(nullptr);
	firstNode->setPrev(nullptr);
}

template <class Type>
Deque<Type>& Deque<Type>::operator=(const Deque& other) {
	if (&other == this) return *this;
	
	Node<Type>* iterNode = firstNode;
	while (iterNode != nullptr){
		Node<Type>* nextNode = iterNode->getNext();
		delete iterNode;
		iterNode = nextNode;
	}

	Node<Type>* thisNode = new Node<Type>(other.firstNode->getData());
	this->firstNode = thisNode;

	Node<Type>* otherNode = other.firstNode->getNext();
	while (otherNode != nullptr){
		thisNode->setNext( 		new Node<Type>(otherNode->getData())	);
		otherNode = otherNode->getNext();
		Node<Type>* tempNode = thisNode;
		thisNode = thisNode->getNext();
		thisNode->setPrev(tempNode);
		
	}
	lastNode = thisNode;
	lastNode->setNext(nullptr);
	firstNode->setPrev(nullptr);

	this->s = other.s;

	return *this;


}

template <class Type>
bool Deque<Type>::isEmpty() {
	return s == 0;
}

template <class Type>
int Deque<Type>::size() {
	return s;
}

template <class Type>
Type Deque<Type>::first() {
	return (	(firstNode == nullptr) ? Type() : firstNode->getData()	);
}

template <class Type>
Type Deque<Type>::last() {
	return (	(lastNode == nullptr) ? Type() : lastNode->getData()	);
}

template <class Type>
void Deque<Type>::insertFirst(Type o) {
	Node<Type>* newNode = new Node<Type>(o);
	s += 1;
	if (firstNode == nullptr && lastNode == nullptr) {
		lastNode = newNode;
	}
	else if (firstNode == lastNode) {
		lastNode->setNext(nullptr);
		lastNode->setPrev(newNode);
		newNode->setNext(lastNode);
	}
	else {
		newNode->setNext(firstNode);
		firstNode->setPrev(newNode);
	}

	firstNode = newNode;
}

template <class Type>
void Deque<Type>::insertLast(Type o) {
	Node<Type>* newNode = new Node<Type>(o);
	s += 1;
	if (firstNode == nullptr && lastNode == nullptr) {
		firstNode = newNode;
	}
	else if (firstNode == lastNode) {
		firstNode->setPrev(nullptr);
		firstNode->setNext(newNode);
		newNode->setPrev(firstNode);
	}
	else{
		lastNode->setNext(newNode);
		newNode->setPrev(lastNode);
	}

	lastNode = newNode;
	return;
}

template <class Type>
Type Deque<Type>::removeFirst() {
	if (s == 0) throw std::out_of_range("No head node. Likely empty list");
	
	Type nodeData = firstNode->getData();
	if (lastNode == firstNode){
		delete firstNode;
		firstNode = nullptr;
		lastNode = nullptr;
	}
	else
	{
		Node<Type>* newFirstNode = firstNode->getNext();
		newFirstNode->setPrev(nullptr);
		delete firstNode;
		firstNode = newFirstNode;
	}

	s -= 1;
	return nodeData;
}

template <class Type>
Type Deque<Type>::removeLast() {
	if (s == 0) throw std::out_of_range("No tail node. Likely empty list");
	
	Type nodeData = lastNode->getData();
	if (lastNode == firstNode){
		delete lastNode;
		firstNode = nullptr;
		lastNode = nullptr;
	}
	else
	{
		Node<Type>* newLastNode = lastNode->getPrev();
		newLastNode->setNext(nullptr);
		delete lastNode;
		lastNode = newLastNode;
	}

	s -= 1;
	return nodeData;
}

#endif
