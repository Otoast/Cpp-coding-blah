#ifndef NODE_H
#define NODE_H

template <class Type>
class Node {
private:
	Type data;
	Node<Type>* next;
	Node<Type>* prev;

public:
	Node(Type data) {
		this->data = data;
		this->next = nullptr;
		this->prev = nullptr;
	}

	Node(Type data, Node<Type>* next, Node<Type>* prev) {
		this->data = data;
		this->next = next;
		this->prev = prev;
	}

	void setData(Type data) {
		this->data = data;
	}

	Type getData() {
		return this->data;
	}

	void setNext(Node<Type>* next) {
		this->next = next;
	}

	Node<Type>* getNext() {
		return this->next;
	}

	void setPrev(Node<Type>* prev) {
		this->prev = prev;
	}

	Node<Type>* getPrev() {
		return this->prev;
	}
};

#endif