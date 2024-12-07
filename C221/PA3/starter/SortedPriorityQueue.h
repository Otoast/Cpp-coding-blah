#ifndef SORTED_PRIORITY_QUEUE_H
#define SORTED_PRIORITY_QUEUE_H

#include "AbstractPriorityQueue.h"

template <typename Type>
class SortedPriorityQueue : public AbstractPriorityQueue<Type> {
    private:
        Type *arr;
        int capacity;
        int size;

    public:
        SortedPriorityQueue();

        ~SortedPriorityQueue();

        void pq_insert(Type value);

        Type pq_delete();

        Type pq_get_min();

        int pq_size();
};

template <typename Type>
SortedPriorityQueue<Type>::SortedPriorityQueue() : 
    arr(new Type[10]),
    capacity(10),
    size(0){}

template <typename Type>
SortedPriorityQueue<Type>::~SortedPriorityQueue(){
   delete [] arr;
}

template <typename Type>
void SortedPriorityQueue<Type>::pq_insert(Type value) {
    if (size >= capacity){
        Type* newArr = new Type[capacity * 2];
        capacity *= 2;
        for (int i = 0; i < size; ++i) newArr[i] = arr[i];
        delete [] arr;
        arr = newArr;
    }
    arr[size++] = value;
    bool sorted = false;
    for (int i = size - 1; !sorted && i > 0; --i){
        if (arr[i] < arr[i - 1]){
            arr[i] = arr[i - 1];
            arr[i - 1] = value;
        }
        else sorted = true;
    }
}

template <typename Type>
Type SortedPriorityQueue<Type>::pq_delete(){
    if (size == 0) throw std::out_of_range("Empty heap.");
    else if (size == 1) return arr[--size];
    Type popped_item = arr[0];
    for (int i = 1; i < size; ++i){
        arr[i - 1] = arr[i];
    }
    size--;
    return popped_item;
}

template <typename Type>
Type SortedPriorityQueue<Type>::pq_get_min(){
    if (size == 0) throw std::out_of_range("Empty heap.");
    return arr[0];
}

template <typename Type>
int SortedPriorityQueue<Type>::pq_size(){
    return size;
}

#endif