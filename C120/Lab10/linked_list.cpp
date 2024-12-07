# include "linked_list.h"
# include <iostream>
# include <string>

using std::cout, std::endl, std::string, std::ostream;

void MyList::add(const std::string& name, int score) {
    MyNode* newNode = new MyNode(name, score);
    _size++;

    if (_head == nullptr){ 
        _head = newNode;
    }
    else if (_head->next == nullptr){
        _head->next = newNode;
        newNode->prev = _head;
    }
    else {
        MyNode* prevNode = new MyNode(*_tail);
        prevNode->prev->next = prevNode;
        delete _tail;
        prevNode->next = newNode;
        newNode->prev = prevNode;
    }

    _tail = newNode;
 
}

void MyList::clear() {

    if (_head == nullptr) return;
    MyNode* node = _head;
    while (node != nullptr){
        MyNode* tempNode = node->next;
        delete node;
        node = tempNode;
    }
    _head = nullptr;
    _tail = nullptr;
    _size = 0;

}

bool MyList::remove(const std::string& name) {
    // TODO

    return false;
}

bool MyList::insert(const std::string& name, int score, size_t index) {
    // TODO

    return false;
}

MyList::MyList() : _size(0), _head(nullptr), _tail(nullptr) {}

MyList::~MyList() {
    clear();
}

size_t MyList::size() const {
    return _size;
}

bool MyList::empty() const {
    return _head == nullptr;
}

MyNode* MyList::head() const {
    return _head;
}

ostream& operator<<(ostream& os, const MyList& myList) {
    MyNode* _current = myList.head();
    if (_current == nullptr) {
        os << "<empty>" << endl;
        return os;
    }

    os << "[ " << _current->name << ", " << _current->score << " ]";
    _current = _current->next;
    while (_current != nullptr) {
        os << " --> [ " << _current->name << ", " << _current->score << " ]";
        _current = _current->next;
    }
    
    return os;
}

MyNode::MyNode(const std::string& name, int score) : name{name}, score{score}, next{nullptr}, prev{nullptr} {}
