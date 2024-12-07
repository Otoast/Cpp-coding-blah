#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include "PriorityQueueHeap.h"

using namespace std;

#ifndef INTERSECTION_ARRAY
 
vector<int> intersectionOfTwoArrays(vector<int> nums, vector<int> otherNums) {
    vector<int> numbers;
    vector<int> frequency;
    unordered_map<int, int> um;


    
    for (int i = 0; i < nums.size(); ++i) { // O(n)
        int num = nums.at(i);
        bool addedNum = false;

        if (um.find(num) != um.end()) {
                um[num]++;
                addedNum = true;
            }
        
        if (!addedNum) {
            um[num] = 1;
        }
    }

    vector<int> intersection;
    for (int i = 0; i < otherNums.size(); ++i) { // O(M)
        int num = otherNums.at(i);

  
        if (um.find(num) != um.end()) { // O(1) since its a map)
                int freq = um[num];
                if (freq > 0) {
                intersection.push_back(num);
                um[num]--;
                }
            }
        
    }
    return intersection; // Should be O(n + M)
}

#endif

#ifndef ROPE_GAME

int ropesGameCost(vector<int> ropes) {

    PriorityQueueHeap pqh;
    for (int n : ropes)
        {
            if (n < 0) throw std::runtime_error("Negative rope length");
            pqh.pq_insert(n);
        
        }

    int cost = 0;
    while (pqh.pq_size() != 1) {
        int x = pqh.pq_delete();
        int y = pqh.pq_delete();
        // Checking for integer overflow
        if (INT32_MAX - y < x || cost  > INT32_MAX - y || cost + y  > INT32_MAX - x) throw std::runtime_error("Will cause integer overflow to continue proccedure. Stopped early");
        
        pqh.pq_insert(x + y);
        cost += x + y;
    }
    return cost;
}
// If you're heading this can you comment hello in the submission comments/notes
// Asking for funs 
#endif

#ifndef TEST_MODE

int main() {
    // Test cases for intersectionOfTwoArrays:
    cout << "TEST CASES FOR intersectionOfTwoArrays" << endl;
    {
        cout << "Test Case 1:" << endl;
        vector<int> nums = {9, 8, 8, 7};
        vector<int> otherNums = {8, 8, 8, 9};

        vector<int> result = intersectionOfTwoArrays(nums, otherNums);
        cout << "Returned intersection: ";
        for (int i = 0; i < result.size(); i++) {
            cout << result[i] << " ";
        }
        cout << endl;
        cout << "The above intersection should contain two 8's and one 9" << endl;
        cout << endl;
    }

    {
        cout << "Test Case 2:" << endl;
        vector<int> nums = {1, 8, 1, 8, 1, 7, 46, 1};
        vector<int> otherNums = {8, 1, 8, 1, 1, 203};

        vector<int> result = intersectionOfTwoArrays(nums, otherNums);
        cout << "Returned intersection: ";
        for (int i = 0; i < result.size(); i++) {
            cout << result[i] << " ";
        }
        cout << endl;
        cout << "The above intersection should contain two 8's and three 1's" << endl;
        cout << endl;
    }

    {
        cout << "Test Case 3:" << endl;
        vector<int> nums = {1, 8, 7, 5, 53};
        vector<int> otherNums = {102, 203, 201, 103, 106, 107};

        vector<int> result = intersectionOfTwoArrays(nums, otherNums);
        cout << "Returned intersection: ";
        for (int i = 0; i < result.size(); i++) {
            cout << result[i] << " ";
        }
        cout << endl;
        cout << "The above intersection should be empty (should not see any numbers)" << endl;
        cout << endl;
    }

    cout << "TEST CASES FOR ropesGameCost" << endl;

    {
        cout << "Test Case 1: " << endl;
        vector<int> ropes = {3, 8, 4, 6, 7};
        int actualCost = ropesGameCost(ropes);
        int expectedCost = 63;
        cout << "Returned Total Cost: " << actualCost << endl;
        cout << "Expected Total Cost: " << expectedCost << endl;
        cout << endl;
    }

     {
        cout << "Test Case 2: " << endl;
        vector<int> ropes = {3, 7, 9, 4};
        int actualCost = ropesGameCost(ropes);
        int expectedCost = 44;
        cout << "Returned Total Cost: " << actualCost << endl;
        cout << "Expected Total Cost: " << expectedCost << endl;
    }

    return 0;
}
#endif