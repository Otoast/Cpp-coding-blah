#include "PriorityQueueHeap.h"
using namespace std;

#ifndef TEST
int main() {
    PriorityQueueHeap<int> pqh;

    for (int i = 15; i > -1; --i) pqh.pq_insert(i);

    
    pqh.pq_top();
    for (int i = pqh.pq_size(); i > 12; --i){
        pqh.pq_delete();
        pqh.pq_top();
    }

    return 0;
}
#endif