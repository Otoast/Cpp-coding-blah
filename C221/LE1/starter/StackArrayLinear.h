#ifndef STACK_LINEAR_ARRAY_H
#define STACK_LINEAR_ARRAY_H
#include "AbstractStack.h"

template <typename T>
class StackArrayLinear : public AbstractStack<T> {
private:
    T* data;
    int length;
    int topIndex;

public:
    StackArrayLinear();

    ~StackArrayLinear();

    StackArrayLinear(const StackArrayLinear& other);

    StackArrayLinear& operator=(const StackArrayLinear& other);

    bool isEmpty();

    int size();

    T& top();

    T pop();

    void push(const T& e);

};

// Your implementation here
template <typename T>
StackArrayLinear<T>::StackArrayLinear() : 
    data(new T[1]),
    length(1),
    topIndex(-1){}
    
template <typename T>
StackArrayLinear<T>::~StackArrayLinear(){
    delete[] data;
    data = nullptr;
    length = 0;
    topIndex = -1;
}

template <typename T>
StackArrayLinear<T>::StackArrayLinear(const StackArrayLinear& other) {
    this->length = other.length;
    this->topIndex = other.topIndex;
    T* newData = new T[other.length];
    for (int i = 0; i < other.length; ++i){
        newData[i] = other.data[i];
    }
    this->data = newData;
}

template <typename T>
StackArrayLinear<T>& StackArrayLinear<T>::operator=(const StackArrayLinear& other) {
    if (this == &other) return *this;
    this->length = other.length;
    this->topIndex = other.topIndex;
    delete[] this->data;
    T* newData = new T[other.length];
    for (int i = 0; i < other.length; ++i){
        newData[i] = other.data[i];
    }
    this->data = newData;
    return *this;
}

template <typename T>
bool StackArrayLinear<T>::isEmpty(){
    if (topIndex < 0) return true;
    else return false;
}

template <typename T>
int StackArrayLinear<T>::size(){
    return topIndex + 1;
}

template <typename T>
T& StackArrayLinear<T>::top(){
    if (isEmpty()) throw std::out_of_range("STACK IS EMPTY. INITIATING MEMORY WIPE SEQUENCE");
    else return data[topIndex];
}

template <typename T>
T StackArrayLinear<T>::pop(){
    if (isEmpty()) throw std::out_of_range("STACK IS EMPTY. INITIATING MEMORY WIPE SEQUENCE");
    topIndex -= 1;
    return data[topIndex + 1];
}


template <typename T>
void StackArrayLinear<T>::push(const T& e){
    if (topIndex + 1 == length){
        T* newData = new T[length + 10];
        for (int i = 0; i < length; ++i){
            newData[i] = data[i];
        }
        delete [] data;
 
        data = newData;
        length += 10;
    }
    topIndex += 1;
    data[topIndex] = e;

}

#endif