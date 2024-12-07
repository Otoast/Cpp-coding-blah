#ifndef STACK_LinkedList_H
#define STACK_LinkedList_H
#include "AbstractStack.h"

template <typename T>
class Node {
public:
    T data;
    Node<T>* next;
};

template <typename T>
class StackLinkedList : public AbstractStack<T>{
private:
    Node<T>* head;
    int length;
public:
    StackLinkedList();

    ~StackLinkedList();

    StackLinkedList(const StackLinkedList& other);

    StackLinkedList& operator=(const StackLinkedList& other);

    bool isEmpty();

    int size();

    T& top();

    T pop();

    void push(const T& e);

};

// Your implementation here
template <typename T>
StackLinkedList<T>::StackLinkedList() :
    head(nullptr),
    length(0){}

template <typename T>
StackLinkedList<T>::~StackLinkedList(){
    Node<T>* tempNode = head; 
    while (tempNode != nullptr){
        Node<T>* nextNode = tempNode->next;
        delete tempNode;
        tempNode = nextNode;// Potential accessing problem where vanguard says sumn like "YOU CANT ASSIGN A NODE THAT ISNT BLAH BLAH BLAH"
    }
    head = nullptr;
    length = 0;
}

template <typename T>
StackLinkedList<T>::StackLinkedList(const StackLinkedList& other) {
    Node<T>* newHead = new Node<T>();
    newHead->data = other.head->data;
    Node<T>* otherNextNode = other.head->next;
    Node<T>* thisNode = newHead;
    while (otherNextNode != nullptr){
        thisNode->next = new Node<T>();
        thisNode->next->data = otherNextNode->data;
        thisNode->next->next = nullptr;
        otherNextNode = otherNextNode->next;
        thisNode = thisNode->next;
    }
    this->head = newHead;
    length = other.length;
}

template <typename T>
StackLinkedList<T>& StackLinkedList<T>::operator=(const StackLinkedList& other) {
    if (this == &other) return *this;
    while (!this->isEmpty()){
        this->pop();
    }
    this->head = new Node<T>();

    Node<T>* thisNode = this->head;
    Node<T>* otherNode = other.head;
    while (otherNode->next != nullptr){
        thisNode->data = otherNode->data;
        thisNode->next = new Node<T>();
        otherNode = otherNode->next;
        thisNode = thisNode->next;
    }
    thisNode->data = otherNode->data;
    thisNode->next = nullptr;


    this->length = other.length;
    return *this;
}

template <typename T>
bool StackLinkedList<T>::isEmpty(){
    return length == 0;
}

template <typename T>
int StackLinkedList<T>::size(){
    return length;
}

template <typename T>
T& StackLinkedList<T>::top(){
    if (isEmpty()) throw std::out_of_range("STACK IS EMPTY. INITIATING MEMORY WIPE SEQUENCE");
    Node<T>* tempNode = head;
    while (tempNode->next != nullptr){
        tempNode = tempNode->next;
    }
    return tempNode->data;
}

template <typename T>
T StackLinkedList<T>::pop(){
    if (isEmpty()) throw std::out_of_range("STACK IS EMPTY. INITIATING MEMORY WIPE SEQUENCE");
    T data;
    Node<T>* iterNode = head;
    if (head->next == nullptr){
        data = head->data;
        delete head;    head = nullptr;
    }
    else{
        while (iterNode->next->next != nullptr){
            iterNode = iterNode->next;
        }
        Node<T> popNode = *(iterNode->next);
        data = popNode.data;
        delete iterNode->next;
        iterNode->next = nullptr;
    }

    length -= 1;
    return data;
    
}

template <typename T>
void StackLinkedList<T>::push(const T& e){
    if (head == nullptr){
        head = new Node<T>();
        head->data = e;
        head->next = nullptr;
        }
    else{
        Node<T>* iterNode = head;
        while (iterNode->next != nullptr){
            iterNode = iterNode->next;
        }
        iterNode->next = new Node<T>();
        iterNode->next->data = e;
        iterNode->next->next = nullptr;
    }
    length += 1;
}


#endif