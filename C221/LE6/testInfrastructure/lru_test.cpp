#define TEST
#include "lru.h"
#include <iostream>
#include <cassert>

int runLRUCacheTests() {
    int score = 0;

    // Test Case 1: Basic Insertion and Retrieval
    LRUCache cache1(3);
    cache1.insertKeyValue("mango", 10);
    cache1.insertKeyValue("apple", 20);
    cache1.insertKeyValue("guava", 30);
    if (cache1.mostRecentKey() == "guava") {
        score += 3;
        std::cout << "Test Case 1 passed: Most recent key is guava\n";
    } else {
        std::cout << "Test Case 1 failed: Most recent key is not guava\n";
    }

    // Test Case 2: Update Existing Key
    cache1.insertKeyValue("mango", 40);
    if (cache1.mostRecentKey() == "mango") {
        cache1.insertKeyValue("guava", 90);
        if (cache1.mostRecentKey() == "guava") {
            score += 3;
            std::cout << "Test Case 2 passed: Most recent key is guava\n";
        } else {
            std::cout << "Test Case 2 failed: Most recent key is not guava\n";
        }
    } else {
        std::cout << "Test Case 2 failed: Most recent key is not mango\n";
    }

    // Test Case 3: Retrieve Value
    int* mangoValue = cache1.getValue("mango");
    if (mangoValue != nullptr && *mangoValue == 40 && cache1.mostRecentKey() == "mango") {
        int* appleValue = cache1.getValue("apple");
        if (appleValue != nullptr && *appleValue == 20 && cache1.mostRecentKey() == "apple") {
            score += 5;
            std::cout << "Test Case 3 passed: Correct state for apple\n";
        } else {
            std::cout << "Test Case 3 failed: Incorrect state for apple\n";
        }
    } else {
        std::cout << "Test Case 3 failed: Incorrect state for mango\n";
    }

    
    // Test Case 4: Insert Additional Items (Cache Full)
    cache1.insertKeyValue("banana", 20);
    int temp_score = 0;
    if (cache1.getValue("guava") == nullptr && cache1.mostRecentKey() == "banana") {
        cache1.insertKeyValue("orange", 3);
        cache1.insertKeyValue("pineapple", 2);
        
        if (cache1.mostRecentKey() == "pineapple") {
            int* orangeValue = cache1.getValue("orange");
            
            if (orangeValue != nullptr && *orangeValue == 3 && cache1.mostRecentKey() == "orange" 
                        && cache1.getValue("mango") == nullptr && cache1.getValue("apple") == nullptr) {
                int* pineappleValue = cache1.getValue("pineapple");
                if (pineappleValue != nullptr && *pineappleValue == 2 && cache1.mostRecentKey() == "pineapple") {
                    score += 5;
                    temp_score = 5;
                    std::cout << "Test Case 4 passed: Correct cache state after inserting additional items\n";
                } 
            }
        }
    }
    if (temp_score == 0) {
        std::cout << "Test Case 4 failed: Incorrect cache state after inserting additional items\n";
    }

    // Test Case 5: Non-Existent Keys
    if (cache1.getValue("fruits") == nullptr && cache1.mostRecentKey() == "pineapple") {
        score += 1;
        std::cout << "Test Case 5 passed: Correct handling of non-existent key\n";
    } else {
        std::cout << "Test Case 5 failed: Incorrect handling of non-existent key\n";
    }

    // Test Case 6: Empty Cache
    LRUCache emptyCache(1);
    if (emptyCache.mostRecentKey() == "") {
        score += 1;
        std::cout << "Test Case 6 passed: Most recent key is empty\n";
    } else {
        std::cout << "Test Case 6 failed: Most recent key is not empty\n";
    }

    // Test Case 7: Cache Size Limit
    LRUCache smallCache(1);
    smallCache.insertKeyValue("one", 1);
    smallCache.insertKeyValue("two", 2);  // Evicts "one"
    if (smallCache.getValue("one") == nullptr && smallCache.mostRecentKey() == "two") {
        score += 2;
        std::cout << "Test Case 7 passed: Correct eviction in small cache\n";
    } else {
        std::cout << "Test Case 7 failed: Incorrect eviction in small cache\n";
    }

    return score;
}

int main() {
    int totalScore = 0;
    try {
        totalScore = runLRUCacheTests();
    } catch(std::exception& e) {
        cout << e.what() << endl;
    }
    
    std::cout << "Total Score: " << totalScore << " / 20" << endl;
    return 0;
}