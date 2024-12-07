#define TEST
#include <iostream>
#include <vector>
#include <functional> 
#include <random>    
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include "PriorityQueueHeap.h"
using namespace std;

int testPqInsert(){
    PriorityQueueHeap<int> pq;
    int n = rand() % 50 + 41;

    int minNum = 1000;
    for (int i = 0; i < n; i++) {
        int z = rand() % 200 + 25;
        pq.pq_insert(z);
        minNum = min(z, minNum);
    }

    if (pq.pq_top() != minNum) {
        return 0;
    } 
    if (pq.pq_size() != n) {
        return 0;
    }


    PriorityQueueHeap<int, std::less<int>> pq2;
    n = rand() % 50 + 41;

    int maxNum = -1;
    for (int i = 0; i < n; i++) {
        int z = rand() % 200 + 25;
        pq2.pq_insert(z);
        maxNum = max(z, maxNum);
    }

    if (pq2.pq_top() != maxNum) {
        return 0;
    } 
    if (pq2.pq_size() != n) {
        return 0;
    }

    return 7;
}

int testPqEmpty() {
    PriorityQueueHeap<int> pq;
    int n = rand() % 5 + 3;

    if (!pq.is_pq_empty()) {
        return 0;
    }

    for (int i = 0; i < n; i++) {
        pq.pq_insert(rand() % 20);
        if (pq.is_pq_empty()) {
            return 0;
        }
    }
    for (int i = 0; i < n - 1; i++) {
        pq.pq_delete();
        if (pq.is_pq_empty()) {
            return 0;
        }
    }

    pq.pq_delete();
    if (!pq.is_pq_empty()) {
        return 0;
    }

    return 1;
}

template <typename Compare = std::greater<int>>
int testDelete(Compare compare = Compare()) {
    PriorityQueueHeap<int, Compare> pq(compare);
    
    int n = rand() % 50 + 41;

    int minNum = 1000;
    int maxNum = -1;
    std::vector<int> nums;
    for (int i = 0; i < n; i++) {
        int z = rand() % 200 + 25;
        pq.pq_insert(z);
        minNum = min(z, minNum);
        maxNum = max(z, maxNum);
        nums.push_back(z);
    }

    std::sort(nums.begin(), nums.end());

    if (pq.pq_size() != n) {
        cout << "You have not passed insert; pass insert before you test delete" << endl;
        return 0;
    }

    int count;
    if constexpr (std::is_same<Compare, std::greater<int>>::value) {
        count = 0;
    } else {
        count = n - 1;
    }

    while (!pq.is_pq_empty()) {
        int num = pq.pq_delete();
        if (num != nums[count]) {
            return 0;
        }
        if constexpr (std::is_same<Compare, std::greater<int>>::value) {
            count++;
            if (pq.pq_size() != n - count) {
                return 0;
            }
        } else {
            count--;
            if (pq.pq_size() != count + 1) {
                return 0;
            }
        }
    }

    return 7;
}

int testPqDelete() {
    int score = testDelete(std::greater<int>());
    if (score != 7) {
        return 0;
    }
    score = testDelete(std::less<int>());
    return score;
}   

int testPqDeleteTopException() {
    PriorityQueueHeap<int> pq;
    int n = rand() % 5 + 3;
    for (int i = 0; i < n; i++) {
        pq.pq_insert(i);
    }
    for (int i = 0; i < n; i++) {
        pq.pq_delete();
    }
    try {
        pq.pq_delete();
    } catch(std::out_of_range& e) {
         try {
            pq.pq_top();
        } catch(std::out_of_range& e) {
            return 1;
        }
    }
    return 0;
}

int testPqCopyConstructor() {
    PriorityQueueHeap<int> pq;
    int n = rand() % 50 + 41;

    std::vector<int> nums;
    for (int i = 0; i < n; i++) {
        int z = rand() % 200 + 25;
        pq.pq_insert(z);
        nums.push_back(z);
    }

    std::sort(nums.begin(), nums.end());

    PriorityQueueHeap<int> pq2(pq);

    int count = 0;
    while (!pq.is_pq_empty()) {
        int num = pq.pq_delete();
        if (num != nums[count]) {
            return 0;
        }
        if (pq2.pq_delete() != num) {
            return 0;
        }

        count++;
        if (pq.pq_size() != n - count) {
            return 0;
        }
        if (pq2.pq_size() != n - count) {
            return 0;
        }
    }

    pq.pq_insert(1);
    if (pq2.pq_size() > 0) {
        return 0;
    }

    return 2;
}

int testPqCopyAssignment() {
    PriorityQueueHeap<int> pq;
    int n = rand() % 50 + 41;

    std::vector<int> nums;
    for (int i = 0; i < n; i++) {
        int z = rand() % 200 + 25;
        pq.pq_insert(z);
        nums.push_back(z);
    }

    std::sort(nums.begin(), nums.end());

    PriorityQueueHeap<int> pq2;
    for (int i = 0; i < 2 * n; i++) {
        int z = rand() % 500 + 250;
        pq2.pq_insert(z);
    }

    pq2 = pq;
    if (pq2.pq_size() != pq.pq_size()) {
        return 0;
    }
    pq.pq_insert(-1);
    if (pq2.pq_size() == n + 1) {
        return 0;
    }
    pq.pq_delete();

    int count = 0;
    while (!pq.is_pq_empty()) {
        int num = pq.pq_delete();
        if (num != nums[count]) {
            return 0;
        }
        if (pq2.pq_delete() != num) {
            return 0;
        }

        count++;
        if (pq.pq_size() != n - count) {
            return 0;
        }
        if (pq2.pq_size() != n - count) {
            return 0;
        }
    }

    return 2;
}

int main(){
    std::srand(std::time(0));
    int score = 0;

    try {
        int temp_score = testPqInsert();
        if (temp_score == 0) {
            cout << "TEST PQ_INSERT FAILED" << endl;
        } else {
            cout << "TEST PQ_INSERT PASSED" << endl;
        }
        score += temp_score;

        temp_score = testPqDelete();
        if (temp_score == 0) {
            cout << "TEST PQ_DELETE FAILED" << endl;
        } else {
            cout << "TEST PQ_DELETE PASSED" << endl;
        }
        score += temp_score;

        temp_score = testPqEmpty();
        if (temp_score == 0) {
            cout << "TEST PQ_EMPTY FAILED" << endl;
        } else {
            cout << "TEST PQ_EMPTY PASSED" << endl;
        }
        score += temp_score;

        temp_score = testPqDeleteTopException();
        if (temp_score == 0) {
            cout << "TEST PQ_DELETE_TOP_EXCEPTION FAILED" << endl;
        } else {
            cout << "TEST PQ_DELETE_TOP_EXCEPTION PASSED" << endl;
        }
        score += temp_score;

        temp_score = testPqCopyConstructor();
        if (temp_score == 0) {
            cout << "TEST COPY CONSTRUCTOR FAILED" << endl;
        } else {
            cout << "TEST COPY CONSTRUCTOR PASSED" << endl;
        }
        score += temp_score;

        temp_score = testPqCopyAssignment();
        if (temp_score == 0) {
            cout << "TEST COPY ASSIGNMENT FAILED" << endl;
        } else {
            cout << "TEST COPY ASSIGNMENT PASSED" << endl;
        }
        score += temp_score;

    } catch(exception& e) {
        cout << e.what() << endl;
    }


    cout << "Score: " << score << " / 20" << endl;
    return 0;
}