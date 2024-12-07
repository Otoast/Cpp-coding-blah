#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H

#include <iostream>

using namespace std;

template <typename Type>
class PriorityQueueHeap : public AbstractPriorityQueue<Type> {
private:
    Type *arr;
    int capacity;
    int size;
    
    void minHeapify(int i);
    void bubbleUp(int i);
    int pq_parent(int i);

public:
    PriorityQueueHeap();

    ~PriorityQueueHeap();

    int pq_size();
    
    Type pq_get_min();

    void pq_insert(Type value);

    Type pq_delete();
};

// Your implementation here

template <typename Type>
PriorityQueueHeap<Type>::PriorityQueueHeap() : 
    arr(new Type[10]),
    capacity(10),
    size(0){}

template <typename Type>
PriorityQueueHeap<Type>::~PriorityQueueHeap(){
    delete [] arr;  arr = nullptr;
}

template <typename Type>
int PriorityQueueHeap<Type>::pq_size() {
    return size;
}

template <typename Type>
int PriorityQueueHeap<Type>::pq_parent(int i){
    int parent_index = (i - 1) / 2;
    return (parent_index <= 0) ? 0 : parent_index;
}

template <typename Type>
Type PriorityQueueHeap<Type>::pq_get_min(){
    if (size == 0) throw std::out_of_range("Empty heap.");
    return arr[0];
}

template <typename Type>
void PriorityQueueHeap<Type>::pq_insert(Type x) {
    if (size >= capacity){
        Type *newArr = new Type[capacity * 2];
        capacity *= 2;
        for (int i = 0; i < size; ++i) newArr[i] = arr[i];
        delete [] arr;
        arr = newArr;
    }
    arr[size] = x;
    bubbleUp(size++);
}


template <typename Type>
void PriorityQueueHeap<Type>::bubbleUp(int i){
    if (i == 0) return;
    int parent_index = pq_parent(i);
    if (arr[i] < arr[parent_index]){
        Type temp = arr[i];
        arr[i] = arr[parent_index];
        arr[parent_index] = temp;
        bubbleUp(parent_index);
    }
    
}

template <typename Type>
Type PriorityQueueHeap<Type>::pq_delete(){
    if (size == 0) throw std::out_of_range("Empty heap.");
    Type popped_item = arr[0];
    arr[0] = arr[--size];
    minHeapify(0);

    return popped_item;
}

template <typename Type>
void PriorityQueueHeap<Type>::minHeapify(int i){
    int l_child_index = i * 2 + 1;
    int r_child_index = i * 2 + 2;
    int child_index;
    if (r_child_index >= size){
        if (l_child_index >= size) return;
        child_index = l_child_index;
    }
    else {
        child_index = (arr[l_child_index] < arr[r_child_index]) ? l_child_index : r_child_index;
    }
    
    if (arr[child_index] < arr[i]){
        Type temp = arr[i];
        arr[i] = arr[child_index];
        arr[child_index] = temp;
        minHeapify(child_index);
    }
}

#endif