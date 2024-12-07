#ifndef DOUBLEHASHING_H
#define DOUBLEHASHING_H

#include "AbstractHashTable.h"
#include <vector>

// Double hashing hash table class
class DoubleHashTable : public AbstractHashTable {
    private:
    // helper functions
    int secondHash(std::string s) const;
    std::vector<HashEntry> table;
    int prevPrime;
    void resizeAndRehash();

    public: 
    DoubleHashTable();
    ~DoubleHashTable(); 
    void insert(std::string key, int val); 
    int remove(std::string key); 
    int get(std::string key) const; 
    bool contains(std::string key) const;
};


///////////////////// TODO: FILL OUT THE FUNCTIONS /////////////////////

// constructor 
DoubleHashTable::DoubleHashTable(): AbstractHashTable()
 {
    maxLoadFactor = 0.7;
    capacity = 1;
    table.resize(capacity);
    prevPrime = 7;

	
}

// destructor
DoubleHashTable::~DoubleHashTable() {
    table.clear();
	
}

// inserts the given string key
void DoubleHashTable::insert(std::string key, int val) {
    HashEntry newEntry (key, val);
    if (load_factor() >= maxLoadFactor) resizeAndRehash();
    num_elements++;

    try {remove(key);}
    catch (std::out_of_range) {}

    newEntry.isFilled = true;
    int hashIndex = hash(key);
    
    auto it = table.begin() + hashIndex;
    if (it->key == key && !it->DELETED)         {num_elements--;     *it = newEntry;     return;}
    else if (!it->isFilled)     {*it = newEntry;     return;}

    int i = 1;
    while (it->isFilled) {
        if (it->key == key && !it->DELETED || it->DELETED) break;
        hashIndex = (hash(key) + i++ * secondHash(key)) % capacity;
        it = table.begin() + hashIndex;
    }
    
    if (it->key == key && !it->DELETED) num_elements--;
    *it = newEntry;


}

// removes the given key from the hash table - if the key is not in the list, throw an error
int DoubleHashTable::remove(std::string key) {
	int hashIndex = hash(key);
    auto it = table.begin() + hashIndex;
    if (!it->isFilled) throw std::out_of_range("Cannot find key");
    int i = 1;
    while (it->key != key || it->DELETED) {
        if (i >= capacity || !it->isFilled && !it->DELETED) throw std::out_of_range("Cannot find key");
        hashIndex = (hash(key) + i++ * secondHash(key)) % capacity;
        it = table.begin() + hashIndex;
    }
    it->DELETED = true;
    num_elements--;
    return it->val;
}

// getter to obtain the value associated with the given key
int DoubleHashTable::get(std::string key) const {
	int hashIndex = hash(key);
    auto it = table.begin() + hashIndex;
    if (!it->isFilled) throw std::out_of_range("Cannot find key");
    int i = 1;
    while (it->key != key || it->DELETED) {
        if (i >= capacity || !it->isFilled && !it->DELETED) throw std::out_of_range("Cannot find key");
        hashIndex = (hash(key) + i++ * secondHash(key)) % capacity;
        it = table.begin() + hashIndex;
    }
    return it->val;
}

bool DoubleHashTable::contains(std::string key) const {
	try {
        get(key);
        return true;
    }
    catch (std::out_of_range) { return false; }
}

void DoubleHashTable::resizeAndRehash() {
	prevPrime = capacity;
    capacity = findNextPrime(capacity * 2);
    std::vector<HashEntry> oldTable = table;
    table.clear();
    table.resize(capacity);
    num_elements = 0;
    for (auto it = oldTable.begin(); it != oldTable.end(); ++it){
        if (!it->DELETED && it->isFilled) insert(it->key, it->val);

    }
}

// helper functions 
int DoubleHashTable::secondHash(std::string s) const {
	unsigned long hash = 0;
	int n = s.length();
	unsigned const int c = 23;
	for (int i = 0; i < n; ++i){
		hash = c * hash + int(s[i]);
	}
	return prevPrime - (hash % prevPrime);
}


#endif