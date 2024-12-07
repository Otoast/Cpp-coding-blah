#include "AbstractHashTable.h"
#include "ChainingHashTable.h"
#include "ProbingHashTable.h"
#include "DoubleHashTable.h"
#include <chrono>
#include <iostream>
#include <fstream>
#include <unordered_map>
#include <vector>

using namespace std;

enum OPERATION {
    INSERTION,
    DELETION
};

int testHashTableInsert(AbstractHashTable* aht, std::unordered_map<string, int>& actualMap, vector<string> words) {
    int count = 0;
        
    // auto start = chrono::high_resolution_clock::now();
       
    for (int i = 0; i < words.size(); i++) {
        std::string word = words[i];
        if (!aht->contains(word)) {
            aht->insert(word, 1);
        } else {
            int curVal = aht->get(word);
            aht->insert(word, curVal + 1);
        }

        if (actualMap.find(word) != actualMap.end()) {
            actualMap[word] += 1;
        } else {
            actualMap[word] = 1;
        }
    }

        // auto stop = chrono::high_resolution_clock::now();
        // auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);
        // cout << "Time taken to run algorithm: " << (duration.count() / 1000000) << endl;

    for (auto it = actualMap.cbegin(); it != actualMap.cend(); it++) {
       if (actualMap[it->first] != aht->get(it->first)) {
            return 0;
       }
    }

    if (actualMap.size() != aht->getSize()) {
        return 0;
    }

    return 5;
}

int testHashTableRemove(AbstractHashTable* aht, std::unordered_map<string, int> actualMap) {
    if (actualMap.size() == 0) {
        cout << "You have not passed insert yet" << endl;
        return 0;
    }
    for (auto it = actualMap.cbegin(), next_it = it; it != actualMap.cend(); it = next_it) {
        ++next_it;
        string word = it->first;
        actualMap.erase(it);
        aht->remove(word);
        if (aht->contains(word)) {
            return 0;
        } 
        if (aht->getSize() != actualMap.size()) {
            return 0;
        }
    }

    return 5;
}

int testHashTableInsertAndRemove(AbstractHashTable* aht, vector<string> words) {
    std::unordered_map<string, int> tempMap;
    for (int i = 0; i < words.size() / 2; i++) {
        int rand_idx = rand() % words.size();
        int insert_or_delete = rand() % 2;
        if (insert_or_delete == OPERATION::INSERTION) {
            if (tempMap.find(words[rand_idx]) != tempMap.end()) {
                tempMap[words[rand_idx]] += 1;
            } else {
                tempMap[words[rand_idx]] = 1;
            }
            if (aht->contains(words[rand_idx])) {
                int curValue = aht->get(words[rand_idx]);
                aht->insert(words[rand_idx], curValue + 1);
            } else {
                aht->insert(words[rand_idx], 1);
            }
        }
        else if (insert_or_delete == OPERATION::DELETION) {
            if (tempMap.find(words[rand_idx]) != tempMap.end()) {
                tempMap.erase(tempMap.find(words[rand_idx]));
            } 
            if (aht->contains(words[rand_idx])) {
                aht->remove(words[rand_idx]);
            } else {
                try {
                    aht->remove(words[rand_idx]);
                } catch (std::out_of_range& e) {
                    continue;
                }
            }
        }
    }

    for (auto it = tempMap.cbegin(); it != tempMap.cend(); it++) {
       if (tempMap[it->first] != aht->get(it->first)) {
        cout << "First item is: " << tempMap[it->first] << " Instead is " << aht->get(it->first) << endl;
            return 0;
       }
    }

    if (tempMap.size() != aht->getSize()) {
        return 0;
    }

    return 10;
}

int testHashTable(AbstractHashTable* aht, vector<string> words) {
    int score = 0;
    try {
        std::unordered_map<string, int> actualMap;
        int temp_score = testHashTableInsert(aht, actualMap, words);
        if (temp_score == 0) {
            cout << "Failed insert" << endl;
        } else {
            cout << "Passed insert" << endl;
        }
        score += temp_score;
        temp_score = testHashTableRemove(aht, actualMap);
        if (temp_score == 0) {
            cout << "Failed remove" << endl;
        } else {
            cout << "Passed remove" << endl;
        }
        score += temp_score;
        temp_score = testHashTableInsertAndRemove(aht, words);
        if (temp_score == 0) {
            cout << "Failed insert & remove together" << endl;
        } else {
            cout << "Passed insert & remove together" << endl;
        }
        score += temp_score;
    } catch(std::exception& e) {
        cout << e.what() << endl;
    }

    cout << endl;

    return score;
}

int main() {
    std::string filename = "dictionary.txt";
    std::ifstream file(filename);
    std::srand(time(NULL));
    if (!file.is_open()) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return 0;
    }

    vector<string> words;
    std::string word;
    while (file >> word) {
        words.push_back(word);
    }

    int finalScore = 0;
    cout << "Chaining Hash Table" << endl;
    AbstractHashTable* cht = new ChainingHashTable();
    finalScore += testHashTable(cht, words);
    delete cht;  

    
    cout << "Probing Hash Table" << endl;
    AbstractHashTable* pht = new ProbingHashTable();
    finalScore += testHashTable(pht, words);
    delete pht; 

    cout << "Double Hash Table" << endl;
    AbstractHashTable* dht = new DoubleHashTable();
    finalScore += testHashTable(dht, words);
    delete dht;    

    cout << "Your final score is: " << finalScore << " / 60" << endl;
    
    return 0;
}