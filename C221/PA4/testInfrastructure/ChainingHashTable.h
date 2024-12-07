#ifndef CHAINING_H
#define CHAINING_H

#include "AbstractHashTable.h"
#include <vector>
#include <list>


// Chaining hash table class
class ChainingHashTable: public AbstractHashTable {
    private:
    std::vector<std::list<HashEntry>> table;
    void resizeAndRehash();

    public: 
    ChainingHashTable();
    ~ChainingHashTable(); 
    void insert(std::string key, const int val); 
    int remove(std::string key); 
    int get(std::string key) const;
    bool contains(std::string key) const;
};


///////////////////// TODO: FILL OUT THE FUNCTIONS /////////////////////

// constructor
ChainingHashTable::ChainingHashTable(): AbstractHashTable()
    { 
        maxLoadFactor = 3;
        table.resize(capacity);
    }   

// destructor
ChainingHashTable::~ChainingHashTable() {
    table.clear();
}

// inserts the given string key
void ChainingHashTable::insert(std::string key, int val) {
    HashEntry newEntry (key, val);
    if (load_factor() >= maxLoadFactor) resizeAndRehash();
    num_elements++;
    int hashIndex = hash(key);
    
    auto &valueList = table.at(hashIndex);
    if (valueList.size() == 0) {
        valueList.push_back(newEntry);
        return;
    }

    auto it = valueList.begin();
    bool foundVacancy = false;
    HashEntry* vacSpace;

    for (it; it != valueList.end(); ++it) {
        if (it->key == key && !it->DELETED) {
            *it = newEntry;
            num_elements--;
            return;
        }
        else if (it->DELETED && foundVacancy) {
            vacSpace = &(*it);
            foundVacancy = true;
        }
    }
    if (foundVacancy)
       *vacSpace = newEntry;
    else
        valueList.push_back(newEntry);

    
}

// removes the given key from the hash table - if the key is not in the list, throw an error
int ChainingHashTable::remove(std::string key) {
    int hashIndex = hash(key);
    auto it = (table.at(hashIndex)).begin();

    for (it; it != table.at(hashIndex).end(); ++it){
        if (it->key == key && !it->DELETED && it->isFilled){
            it->DELETED = true;
            it->isFilled = false;
            num_elements--;
            return it->val;
        }
    }
    throw std::out_of_range("Key does not exist.");

}

// getter to obtain the value associated with the given key
int ChainingHashTable::get(std::string key) const {
    int hashIndex = hash(key);
    auto it = (table.at(hashIndex)).begin();
    
    for (it; it != table.at(hashIndex).end(); ++it){
        if (it->key == key && !it->DELETED){
            return it->val;
        }
    }
    throw std::out_of_range("Key does not exist.");
}

bool ChainingHashTable::contains(const std::string key) const {
    try {
        int val = get(key);
        return true;
    }
    catch (std::out_of_range) {return false;}
}

void ChainingHashTable::resizeAndRehash() {
    capacity = findNextPrime(capacity * 2);
    std::vector<std::list<HashEntry>> oldTable = table;
    table.clear();
    table.resize(capacity);
    num_elements = 0;
    for (auto it = oldTable.begin(); it != oldTable.end(); ++it){
        for (auto it2 = it->begin(); it2 != it->end(); ++it2){
            if (!it2->DELETED && it2->isFilled) insert(it2->key, it2->val);
        }
    }

}

#endif