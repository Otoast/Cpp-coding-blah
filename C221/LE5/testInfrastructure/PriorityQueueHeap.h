#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H

#include <vector>
#include <iostream>

using namespace std;

template <typename Type, typename Compare = std::greater<Type>>
class PriorityQueueHeap {
private:
    Compare compare;
    Type *arr;
    int capacity;
    int size;

    void heapify(int i);
    void bubbleUp(int i);
    int pq_parent(int i);

public:
    PriorityQueueHeap();

    PriorityQueueHeap(const PriorityQueueHeap& other);

    PriorityQueueHeap(const Compare& comp);

    PriorityQueueHeap& operator=(const PriorityQueueHeap& other);

    ~PriorityQueueHeap();

    int pq_size();

    bool is_pq_empty();
    
    Type pq_top();

    void pq_insert(Type x);

    Type pq_delete();
};

// Your implementation here

template <typename Type, typename Compare>
PriorityQueueHeap<Type, Compare>::PriorityQueueHeap() : 
    compare(),
    arr(new Type[10]),
    capacity(10),
    size(0) {}

template <typename Type, typename Compare>
PriorityQueueHeap<Type, Compare>::~PriorityQueueHeap(){
    delete [] arr;  size = 0;   capacity = 0; 
}

template <typename Type, typename Compare>
PriorityQueueHeap<Type, Compare>::PriorityQueueHeap(const Compare& _comp) :
    compare(_comp),
    arr(new Type[10]),
    capacity(10),
    size(0) {}

template <typename Type, typename Compare>
PriorityQueueHeap<Type, Compare>::PriorityQueueHeap(const PriorityQueueHeap& other) : 
    compare(other.compare),
    arr(new Type[other.capacity]),
    capacity(other.capacity),
    size(other.size) {
        for (int i = 0; i < size; ++i) arr[i] = other.arr[i];
    }

template <typename Type, typename Compare>
PriorityQueueHeap<Type, Compare>& PriorityQueueHeap<Type, Compare>::operator=(const PriorityQueueHeap& other) {
    if (&other == this) return *this;
    
    delete [] arr;
    size = other.size;  capacity = other.capacity; compare = other.compare;
    arr = new Type[capacity];
    for (int i = 0; i < size; ++i) arr[i] = other.arr[i];
    return *this;
}

template <typename Type, typename Compare>
int PriorityQueueHeap<Type, Compare>::pq_size() {
    return size;
}

template <typename Type, typename Compare>
bool PriorityQueueHeap<Type, Compare>::is_pq_empty(){
    return size == 0;
}

template <typename Type, typename Compare>
int PriorityQueueHeap<Type, Compare>::pq_parent(int i){
    int parent_index = (i - 1) / 2;
    return (parent_index <= 0) ? 0 : parent_index;
}

template <typename Type, typename Compare>
Type PriorityQueueHeap<Type, Compare>::pq_top(){
    if (is_pq_empty()) throw std::out_of_range("Empty heap.");

    return arr[0];
}

template <typename Type, typename Compare>
void PriorityQueueHeap<Type, Compare>::pq_insert(Type x) {
    if (size >= capacity) {
        Type* newArr = new Type[capacity * 2];
        capacity *= 2;
        for (int i = 0; i < size; ++i) newArr[i] = arr[i];
        delete [] arr;
        arr = newArr;
    }
    arr[size] = x;
    bubbleUp(size++);
}


template <typename Type, typename Compare>
void PriorityQueueHeap<Type, Compare>::bubbleUp(int i){
    if (i == 0) return;
    int p_index = pq_parent(i);
    if (compare(arr[p_index], arr[i])){
        Type temp = arr[i];
        arr[i] = arr[p_index];
        arr[p_index] = temp;
        bubbleUp(p_index);
    }
    
}

template <typename Type, typename Compare>
Type PriorityQueueHeap<Type, Compare>::pq_delete(){
    if (is_pq_empty()) throw std::out_of_range("Empty heap.");
    Type popped_item = arr[0];
    arr[0] = arr[--size];
    heapify(0);
    return popped_item;
}

template <typename Type, typename Compare>
void PriorityQueueHeap<Type, Compare>::heapify(int i){
    int l_child_index = 2 * i + 1;
    int r_child_index = 2 * i + 2;
    int child_index;

    if (r_child_index >= size){
        if (l_child_index >= size) return;
        child_index = l_child_index;
    }
    else child_index = (compare(arr[l_child_index], arr[r_child_index])) ? r_child_index : l_child_index;
    if (compare(arr[i], arr[child_index])) {
        Type temp = arr[i];
        arr[i] = arr[child_index];
        arr[child_index] = temp;
        heapify(child_index);
    }
}

#endif