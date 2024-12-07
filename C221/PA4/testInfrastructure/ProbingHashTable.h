#ifndef LINEARPROBING_H
#define LINEARPROBING_H

#include "AbstractHashTable.h"
#include <vector>

// Linear probing hash table class
class ProbingHashTable : public AbstractHashTable {
    private:
    std::vector<HashEntry> table;
    void resizeAndRehash();
    
    public: 
    ProbingHashTable();
    ~ProbingHashTable(); 
    void insert(std::string key, int val); 
    int remove(std::string key); 
    int get(std::string key) const; 
    bool contains(std::string key) const;
};

///////////////////// TODO: FILL OUT THE FUNCTIONS /////////////////////

// constructor 
ProbingHashTable::ProbingHashTable(): AbstractHashTable() {
	table.resize(capacity);
    maxLoadFactor = 0.7;
}

// destructor
ProbingHashTable::~ProbingHashTable() {
   
}

// inserts the given string key
void ProbingHashTable::insert(std::string key, int val) {
    if (load_factor() >= maxLoadFactor) resizeAndRehash();
    num_elements++;
    HashEntry newEntry (key, val);
    newEntry.isFilled = true;
    int hashIndex = hash(key);

    if ( !table.at(hashIndex).isFilled || table.at(hashIndex).key == key && !table.at(hashIndex).DELETED){ // Checks if hash worked first try
        if (table.at(hashIndex).key == key) num_elements--;
        table.at(hashIndex) = newEntry;
        return;
    }

    /* 
        This one is a doozy. I was hoping to get worst case O(n) by checking for removal of a key without calling the removal function. I messed up so bad at one point i was stumped for
        like 20 hours on why my code wasn't working. I had to break it down granularly so i understood what was going on, hopefully the comments should make a bit of sense to see what the algorithm is checking for as it
        iterates through the list. if not SORRY
    */
    HashEntry* vacSpace;
    bool foundVacancy = false;

    for (auto it = table.begin() + 1 + hashIndex; it != table.end(); ++it){
        if (foundVacancy)
        {
            if (it->key == key && !it->DELETED) { // Case 5: Found a previous vacancy that is better fit, but found key
                it->DELETED = true;
                num_elements--;
                break;
            }
            else if (!it->isFilled) break; // Case 4: Found uninitialized vacant spot, but another spot was found that was better fit (No way key can be past uninitialized value)
        }
        else 
        {
            if (it->key == key && !it->DELETED) { // Case 1: Found key probing, and there wasn't a prior vacant spot that is better fit
                *it = newEntry;
                num_elements--; return;
            }
            else if (!it->isFilled) {  // Case 2: Found uninitialized vacant spot, no prior place that is better fit (No way key can be past uninitialized value)
                *it = newEntry;
                return;
            }
            else if (it->DELETED) {  // Case 3: Found deleted spot, no prior vacancy found. Doesn't mean the original key wasn't later down
                foundVacancy = true;
                vacSpace = &(*it);
            }

        }

    }
    
    if (foundVacancy) {
        *vacSpace = newEntry;
        return;
    }
    
    for (auto it = table.begin(); it != table.begin() + hashIndex; ++it){
        if (foundVacancy)
        {
            if (it->key == key && !it->DELETED) { // Case 5: Found a previous vacancy that is better fit, but found key
                it->DELETED = true;
                num_elements--;
                break;
            }
            else if (!it->isFilled) break; // Case 4: Found uninitialized vacant spot, but another spot was found that was better fit (No way key can be past uninitialized value)
        }
        else 
        {
            if (it->key == key && !it->DELETED) { // Case 1: Found key probing, and there wasn't a prior vacant spot that is better fit
                *it = newEntry;
                num_elements--; return;
            }
            else if (!it->isFilled) {  // Case 2: Found uninitialized vacant spot, no prior place that is better fit (No way key can be past uninitialized value)
                *it = newEntry;
                return;
            }
            else if (it->DELETED) {  // Case 3: Found deleted spot, no prior vacancy found. Doesn't mean the original key wasn't later down
                foundVacancy = true;
                vacSpace = &(*it);
            }

        }
    }

    if (foundVacancy) {
        *vacSpace = newEntry;
        return;
    }
	
}

// removes the given key from the hash table - if the key is not in the list, throw an error
int ProbingHashTable::remove(std::string key) {
    int hashIndex = hash(key);

    for (auto it = table.begin() + hashIndex; it != table.end(); ++it){
        if (!it->DELETED && key == it->key){
            it->DELETED = true;
            num_elements--;
            return it->val;
        }
        if (!it->DELETED && !it->isFilled) throw std::out_of_range("Could not find key");
    }
    for (auto it = table.begin(); it != table.begin() + hashIndex; ++it){
        if (!it->DELETED && key == it->key){
            it->DELETED = true;
            num_elements--;
            return it->val;
        }
        if (!it->DELETED && !it->isFilled) throw std::out_of_range("Could not find key");
    }
    throw std::out_of_range("Bad key");
}

// getter to obtain the value associated with the given key
int ProbingHashTable::get(std::string key) const {
    int hashIndex = hash(key);

    for (auto it = table.begin() + hashIndex; it != table.end(); ++it){
        if (!it->DELETED && key == it->key) return it->val;
        else if (!it->isFilled && !it->DELETED) throw std::out_of_range("Bad key cant get");
    }
    for (auto it = table.begin(); it != table.begin() + hashIndex; ++it){
        if (!it->DELETED && key == it->key) return it->val;
        else if (!it->isFilled && !it->DELETED) throw std::out_of_range("Bad key cant get");
    }
    throw std::out_of_range("Bad key");
}

bool ProbingHashTable::contains(std::string key) const {
    try {
        get(key);
        return true;
    }
    catch (std::out_of_range) {     return false;    }
}

void ProbingHashTable::resizeAndRehash() {
    capacity = findNextPrime(capacity * 2);
    std::vector<HashEntry> oldTable = table;
    table.clear();
    table.resize(capacity);
    num_elements = 0;
    for (auto it = oldTable.begin(); it != oldTable.end(); ++it)
        if (!it->DELETED && it->isFilled) insert(it->key, it->val);
    
}

#endif