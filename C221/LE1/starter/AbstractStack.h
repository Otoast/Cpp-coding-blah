#ifndef ABSTRACT_STACK_H
#define ABSTRACT_STACK_H

#include <stdexcept>
#include <iostream>

using namespace std;

// This is the base class for StackArrayLinear and StackArrayDouble. The only 
// difference between StackArrayLinear and StackArrayDouble is the growth 
// rate. Since stack growth is handled in push(), we declare push() as pure 
// virtual. 
template <class T>
class AbstractStack {
    public:
        AbstractStack() {}
        virtual ~AbstractStack() {}
        virtual bool isEmpty() = 0;
        virtual int size() = 0;
        virtual T& top() = 0;
        virtual T pop() = 0;
        virtual void push (const T& e) = 0;
        
};

#endif