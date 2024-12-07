#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H

#include <iostream>
#include <queue>
using namespace std;

class PriorityQueueHeap {

public:
    priority_queue<int, vector<int>, greater<int>> minHeap;

    PriorityQueueHeap() {

    };

    int pq_size() {
        return minHeap.size();
    };
    
    int pq_get_min() {
        return minHeap.top();
    };

    void pq_insert(int value) {
        minHeap.push(value);
    };

    int pq_delete() {
        int num = minHeap.top();
        minHeap.pop();
        return num;
    };
};

#endif