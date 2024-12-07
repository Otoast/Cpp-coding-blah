#ifndef UNSORTED_PRIORITY_QUEUE_H
#define UNSORTED_PRIORITY_QUEUE_H

#include "AbstractPriorityQueue.h"

template <typename Type>
class UnsortedPriorityQueue : public AbstractPriorityQueue<Type> {
    private:
        Type *arr;
        int capacity;
        int size;

    public:
        UnsortedPriorityQueue();

        ~UnsortedPriorityQueue();

        void pq_insert(Type value);

        Type pq_delete();

        Type pq_get_min();

        int pq_size();
};

template <typename Type>
UnsortedPriorityQueue<Type>::UnsortedPriorityQueue() : 
    arr(new Type[10]),
    capacity(10),
    size(0){}

template <typename Type>
UnsortedPriorityQueue<Type>::~UnsortedPriorityQueue(){
    delete [] arr;
}

template <typename Type>
void UnsortedPriorityQueue<Type>::pq_insert(Type value) {
    if (size >= capacity){
        Type* newArr = new Type[capacity * 2];
        capacity *= 2;
        for (int i = 0; i < size; ++i) newArr[i] = arr[i];
        delete [] arr;
        arr = newArr;
    }

    arr[size++] = value;
}

template <typename Type>
Type UnsortedPriorityQueue<Type>::pq_delete(){
    if (size == 0) throw std::out_of_range("Empty heap.");
    Type min_value = pq_get_min();
    if (--size == 0) return min_value;
    
    bool deleted = false;
    for (int i = 0, j = 0; i < size; ++i, ++j){
        if (!deleted && min_value == arr[i]) {deleted = true;   j++;}
        arr[i] = arr[j];
    }

    return min_value;
}


template <typename Type>
Type UnsortedPriorityQueue<Type>::pq_get_min(){
    if (size == 0) throw std::out_of_range("Empty heap.");
    Type min_value = arr[0];
    for (int i = 0; i < size; ++i)
        if (arr[i] < min_value) min_value = arr[i];
    return min_value;

}

template <typename Type>
int UnsortedPriorityQueue<Type>::pq_size(){
    return size;
}

#endif