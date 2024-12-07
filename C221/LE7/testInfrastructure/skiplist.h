#ifndef SKIPLIST_H
#define SKIPLIST_H

#include <iostream>
#include <vector>
#include <cstdlib>
using namespace std;

class Node {
public:
    int key;
    std::vector<Node*> forward;

    Node(int key, int level) : key(key), forward(level + 1, nullptr) {}
};

class SkipList {
private: 
    double P;
    int MAXLVL;
    Node* header;
    int level;

public:
    SkipList(int max_lvl, double p);
    ~SkipList();
    int randomLevel();
    void insertElement(int key);
    void deleteElement(int search_key);
    bool searchElement(int key);
    void displayList();
};


SkipList::SkipList(int max_lvl, double p) : MAXLVL(max_lvl), P(p), level(0) {
    header = new Node(-1, MAXLVL);
}

SkipList::~SkipList() {
    Node* iterNode = header->forward.at(0);
    while (iterNode != nullptr) {
        header->forward.at(0) = iterNode->forward.at(0);
        delete iterNode;
        iterNode = header->forward.at(0);

    }
    delete header;

} 

int SkipList::randomLevel() {
    int randLevel = 0;
    bool increase = true;
    while (increase) {
        int coinFlip = rand() % 2;
        if (coinFlip < P && randLevel < MAXLVL) randLevel++;
        else increase = false;
    }
    return randLevel;
}

void SkipList::insertElement(int key) {

    if (searchElement(key)) return;
  
    int currentLevel = randomLevel();
    if (currentLevel > level) level = currentLevel;
    if (currentLevel >= MAXLVL) currentLevel = MAXLVL;
    Node* newEntry = new Node(key, currentLevel);
    Node* currNode = header->forward.at(currentLevel);
    Node* prevNode = header;
    
    while (currentLevel >= 0){
        if (prevNode->key < key && (currNode == nullptr || currNode->key > key)) {
            Node* temp = prevNode->forward.at(currentLevel);
            prevNode->forward.at(currentLevel) = newEntry;
            newEntry->forward.at(currentLevel) = currNode;
            if (currentLevel - 1 >= 0) currNode = prevNode->forward.at(--currentLevel);
            else break;
        }
        
        else {
            prevNode = currNode;
            currNode = currNode->forward.at(currentLevel);   
        }
    }   

}

void SkipList::deleteElement(int search_key) {
    if (!searchElement(search_key)) throw std::runtime_error("Could not find key");
    Node* currNode = header->forward.at(this->level);
    int currentLevel = this->level;
    Node* prevNode = header;
    Node* nodeToDelete;
    while (currentLevel >= 0){
        if (currNode == nullptr || currNode->key > search_key) {
            --currentLevel;
            if (currentLevel >= 0) currNode = prevNode->forward.at(currentLevel);
            continue;
        }
        else if (currNode->key == search_key) {
            prevNode->forward.at(currentLevel) = currNode->forward.at(currentLevel);
            nodeToDelete = currNode;
            currNode = prevNode;
        }
        
        prevNode = currNode;
        currNode = currNode->forward.at(currentLevel);
   
    }

    delete nodeToDelete;

}

bool SkipList::searchElement(int key) {
    Node* currNode = header->forward.at(this->level);
    int currentLevel = this->level;
    Node* prevNode = header;
    while (currentLevel >= 0){
        if (currNode == nullptr || currNode->key > key) {
            --currentLevel;
            if (currentLevel >= 0) currNode = prevNode->forward.at(currentLevel);
            continue;
        }
        else if (currNode->key == key) return true;
        
        prevNode = currNode;
        currNode = currNode->forward.at(currentLevel);
   
    }
    return false;
}

void SkipList::displayList() {
    
    std::cout << "\n*****Skip List******" << std::endl;
    Node* head = header;
    for (int lvl = 0; lvl <= level; lvl++) {
        std::cout << "Level " << lvl << ": ";
        Node* node = head->forward[lvl];
        while (node != nullptr) {
            std::cout << node->key << " ";
            node = node->forward[lvl];
        }
        std::cout << std::endl;
    }
}

#endif