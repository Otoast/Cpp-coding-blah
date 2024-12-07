#ifndef STACK_DOUBLE_ARRAY_H
#define STACK_DOUBLE_ARRAY_H
#include "AbstractStack.h"

template <typename T>
class StackArrayDouble : public AbstractStack<T> {
private:
    T* data;
    int length;
    int topIndex;

public:
    StackArrayDouble();

    ~StackArrayDouble();

    StackArrayDouble(const StackArrayDouble& other);

    StackArrayDouble& operator=(const StackArrayDouble& other);

    bool isEmpty();

    int size();

    T& top();

    T pop();

    void push(const T& e);

};

// Your implementation here
template <typename T>
StackArrayDouble<T>::StackArrayDouble():
    data(new T[1]),
    length(1),
    topIndex(-1){}

template <typename T>
StackArrayDouble<T>::~StackArrayDouble(){
    delete[] data;
    data = nullptr;
    length = 0;
    topIndex = -1;
}

template <typename T>
StackArrayDouble<T>::StackArrayDouble(const StackArrayDouble& other) {
    this->length = other.length;
    this->topIndex = other.topIndex;
    T* newData = new T[other.length];
    for (int i = 0; i < other.length; ++i){
        newData[i] = other.data[i];
    }
    this->data = newData;
}

template <typename T>
StackArrayDouble<T>& StackArrayDouble<T>::operator=(const StackArrayDouble& other) {
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
bool StackArrayDouble<T>::isEmpty(){
    if (topIndex < 0) return true;
    else return false;
}

template <typename T>
int StackArrayDouble<T>::size(){
    return topIndex + 1;
}

template <typename T>
T& StackArrayDouble<T>::top(){
    if (isEmpty()) throw std::out_of_range("STACK IS EMPTY. INITIATING MEMORY WIPE SEQUENCE");
    else return data[topIndex];
}

template <typename T>
T StackArrayDouble<T>::pop(){
    if (isEmpty()) throw std::out_of_range("STACK IS EMPTY. INITIATING MEMORY WIPE SEQUENCE");
    topIndex -= 1;
    return data[topIndex + 1];
}

template <typename T>
void StackArrayDouble<T>::push(const T& e){
    if (topIndex + 1 == length){
        T* newData = new T[length * 2];
        for (int i = 0; i < length; ++i){
            newData[i] = data[i];
        }
        delete [] data; // Assuming theres a potential for memory error/leak here
        data = newData;
        length *= 2;
    }
    topIndex += 1;
    data[topIndex] = e;
}
#endif