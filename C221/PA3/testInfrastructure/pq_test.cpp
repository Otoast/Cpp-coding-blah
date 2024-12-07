#define TEST
#include <iostream>
#include <vector>
#include <random>    
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include "AbstractPriorityQueue.h"
#include "PriorityQueueHeap.h"
#include "UnsortedPriorityQueue.h"
#include "SortedPriorityQueue.h"
using namespace std;

enum PRIORITY_QUEUE_TYPE {
    UNSORTED_ARRAY,
    SORTED_ARRAY,
    HEAP
};

int testPqInsert(AbstractPriorityQueue<int>* pq){
    int n = rand() % 50 + 41;

    int minNum = 1000;
    for (int i = 0; i < n; i++) {
        int z = rand() % 200 + 25;
        pq->pq_insert(z);
        minNum = min(z, minNum);
    }

    if (pq->pq_get_min() != minNum) {
        return 0;
    } 
    if (pq->pq_size() != n) {
        return 0;
    }

    return 7;
}

int testPqDelete(AbstractPriorityQueue<int>* pq) {
    int n = rand() % 50 + 41;

    int minNum = 1000;
    std::vector<int> nums;
    for (int i = 0; i < n; i++) {
        int z = rand() % 200 + 25;
        pq->pq_insert(z);
        minNum = min(z, minNum);
        nums.push_back(z);
    }

    std::sort(nums.begin(), nums.end());

    if (pq->pq_get_min() != minNum) {
        cout << "You have not passed insert; pass insert before you test delete" << endl;
        return 0;
    } 
    if (pq->pq_size() != n) {
        cout << pq->pq_size() << endl;
        cout << n << endl;
        cout << "You have not passed insert; pass insert before you test delete" << endl;
        return 0;
    }

    int count = 0;
    while (pq->pq_size() != 0) {
        int num = pq->pq_delete();
        if (num != nums[count]) {
            return 0;
        }
        count++;

        if (pq->pq_size() != n - count) {
            return 0;
        }
    }

    return 7;
}

int testPqDeleteGetMinException(AbstractPriorityQueue<int>* pq) {
    int n = rand() % 5 + 3;
    for (int i = 0; i < n; i++) {
        pq->pq_insert(i);
    }
    for (int i = 0; i < n; i++) {
        pq->pq_delete();
    }
    try {
        pq->pq_delete();
    } catch(std::out_of_range& e) {
         try {
            pq->pq_get_min();
        } catch(std::out_of_range& e) {
            return 1;
        }
    }
    return 0;
}

AbstractPriorityQueue<int>* instantiatePriorityQueue(PRIORITY_QUEUE_TYPE pq_type) {
    if (pq_type == PRIORITY_QUEUE_TYPE::SORTED_ARRAY) {
        return new SortedPriorityQueue<int>();
    } else if (pq_type == PRIORITY_QUEUE_TYPE::UNSORTED_ARRAY) {
        return new UnsortedPriorityQueue<int>();
    } else {
        return new PriorityQueueHeap<int>();
    }
}

int testPriorityQueue(PRIORITY_QUEUE_TYPE pq_type) {
    int score = 0;
   
    try {
        AbstractPriorityQueue<int>* pq = instantiatePriorityQueue(pq_type);
        int temp_score = testPqInsert(pq);
        if (temp_score == 0) {
            cout << "TEST PQ_INSERT FAILED" << endl;
        } else {
            cout << "TEST PQ_INSERT PASSED" << endl;
        }
        score += temp_score;
        delete pq;

        pq = instantiatePriorityQueue(pq_type);
        temp_score = testPqDelete(pq);
        if (temp_score == 0) {
            cout << "TEST PQ_DELETE FAILED" << endl;
        } else {
            cout << "TEST PQ_DELETE PASSED" << endl;
        }
        score += temp_score;
        delete pq;

        pq = instantiatePriorityQueue(pq_type);
        temp_score = testPqDeleteGetMinException(pq);
        if (temp_score == 0) {
            cout << "TEST PQ_DELETE_GET_MIN_EXCEPTION FAILED" << endl;
        } else {
            cout << "TEST PQ_DELETE_GET_MIN_EXCEPTION PASSED" << endl;
        }
        score += temp_score;
        delete pq;

    } catch(exception& e) {
        cout << e.what() << endl;
    }

    cout << endl;

    return score;
}

int main() {
    std::srand(std::time(0));
    int finalScore = 0;

    cout << "Running tests for Priority Queue - Sorted Array Based" << endl;
    finalScore += testPriorityQueue(PRIORITY_QUEUE_TYPE::SORTED_ARRAY);

    cout << "Running tests for Priority Queue - Unsorted Array Based" << endl;
    finalScore += testPriorityQueue(PRIORITY_QUEUE_TYPE::UNSORTED_ARRAY);

    cout << "Running tests for Priority Queue - Heap Based" << endl;
    finalScore += testPriorityQueue(PRIORITY_QUEUE_TYPE::HEAP);

    cout << "Score: " << finalScore << " / 45" << endl;
    return 0;
}