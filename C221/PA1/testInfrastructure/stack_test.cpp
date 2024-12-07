#define TEST

#include <iostream>
#include <cstdlib> 
#include <vector>
#include <ctime> 
using namespace std;
#include "AbstractStack.h"
#include "StackArrayDouble.h"
#include "StackArrayLinear.h"
#include "StackLinkedList.h"

enum STACK_TYPE {
    ARRAY_LINEAR,
    ARRAY_DOUBLE,
    LINKED_LIST
};

int testStackPush(AbstractStack<int> *s){
    int projectedSize = (std::rand() % 25) + 3; 

    for (int i = 0; i < projectedSize; i++) {
        int randomNumber = std::rand() % 100;
        s->push(randomNumber);
    }
    
    if(s->size() != projectedSize){
        return 0;
    }
    return 1;
}


int testStackPop(AbstractStack<int> *s){
    int projectedSize = (std::rand() % 50) + 5; 

    vector<int> v;
    for (int i = 0; i < projectedSize; i++) {
        int randomNumber = std::rand() % 100;
        v.push_back(randomNumber);
        s->push(randomNumber);
    }

    for (int i = 0; i < projectedSize; i++) {
        if (s->pop() != v[v.size() - (i + 1)]) {
            return 0;
        }
    }

    if (s->size() != 0) {
        return 0;
    }
    
    return 3;
}

int testStackPop_Exception(AbstractStack<int> *s){
    int projectedSize = (std::rand() % 25) + 3; 

    for (int i = 0; i < projectedSize; i++) {
        int randomNumber = std::rand() % 100;
        s->push(randomNumber);
    }

    for (int i = 0; i < projectedSize; i++) {
        s->pop();
    }

    try {
        s->pop();
    } catch(const std::out_of_range& e) {
        return 1;
    }
    return 0;
}

int testStackTop(AbstractStack<int> *s){
    int projectedSize = (std::rand() % 20) + 3; 
    int lastNumber = -1;
    for (int i = 0; i < projectedSize; i++) {
        int randomNumber = std::rand() % 100;
        if (i == projectedSize - 1) {
            lastNumber = randomNumber;
        }
        s->push(randomNumber);
    }

    if(s->top() != lastNumber){
        return 0;
    }
    return 1;
}

int testStackTop_Exception(AbstractStack<int> *s){
   int projectedSize = (std::rand() % 25) + 3; 

    for (int i = 0; i < projectedSize; i++) {
        int randomNumber = std::rand() % 100;
        s->push(randomNumber);
    }

    for (int i = 0; i < projectedSize; i++) {
        s->pop();
    }

    try {
        s->top();
    } catch(const std::out_of_range& e) {
        return 1;
    }
    return 0;
}

int testStackEmpty(AbstractStack<int> *s){
    if(!s->isEmpty()){
        return 0;
    }
    s->push(1);
    if(s->isEmpty()){
        return 0;
    }
    s->pop();
    if(!s->isEmpty()){
        return 0;
    }
    return 1;
}

AbstractStack<int>* instantiateStack(STACK_TYPE stack_type) {
    if (stack_type == STACK_TYPE::ARRAY_DOUBLE) {
        return new StackArrayDouble<int>();
    } else if (stack_type == STACK_TYPE::ARRAY_LINEAR) {
        return new StackArrayLinear<int>();
    } else {
        return new StackLinkedList<int>();
    }
}

int testStackArrayDoubleCopyAssignment() {
    StackArrayDouble<int> s;
    int projectedSize = (std::rand() % 25) + 3; 

    for (int i = 0; i < projectedSize; i++) {
        int randomNumber = std::rand() % 100;
        s.push(randomNumber);
    }

    StackArrayDouble<int> s2;
    int projectedSize2 = (std::rand() % 5) + 3; 

    for (int i = 0; i < projectedSize2; i++) {
        int randomNumber = std::rand() % 200;
        s2.push(randomNumber);
    }

    s2 = s;
    int count = 0;
     while (!s.isEmpty()) {
        count++;
        if (s2.pop() != s.pop()) {
            return 0;
        }
    }
    if (count != projectedSize) {
        return 0;
    }
    return 1;
}

int testStackArrayLinearCopyAssignment() {
    StackArrayLinear<int> s;
    int projectedSize = (std::rand() % 25) + 3; 

    for (int i = 0; i < projectedSize; i++) {
        int randomNumber = std::rand() % 100;
        s.push(randomNumber);
    }

    StackArrayLinear<int> s2;
    int projectedSize2 = (std::rand() % 12) + 3; 

    for (int i = 0; i < projectedSize2; i++) {
        int randomNumber = std::rand() % 200;
        s2.push(randomNumber);
    }

    s2 = s;
    int count = 0;
    while (!s.isEmpty()) {
        count++;
        if (s2.pop() != s.pop()) {
            return 0;
        }
    }

    if (count != projectedSize) {
        return 0;
    }
    return 1;
}

int testStackLinkedListCopyAssignment() {
    StackLinkedList<int> s;
    int projectedSize = (std::rand() % 25) + 3; 

    for (int i = 0; i < projectedSize; i++) {
        int randomNumber = std::rand() % 100;
        s.push(randomNumber);
    }

    StackLinkedList<int> s2;
    int projectedSize2 = (std::rand() % 12) + 3; 

    for (int i = 0; i < projectedSize2; i++) {
        int randomNumber = std::rand() % 200;
        s2.push(randomNumber);
    }

    s2 = s;
    int count = 0;
    while (!s.isEmpty()) {
        count++;
        if (s2.pop() != s.pop()) {
            return 0;
        }
    }

    if (count != projectedSize) {
        return 0;
    }
    return 1;
}

int testStackArrayDoubleCopyConstructor() {
    StackArrayDouble<int> s;
    int projectedSize = (std::rand() % 25) + 3; 

    for (int i = 0; i < projectedSize; i++) {
        int randomNumber = std::rand() % 100;
        s.push(randomNumber);
    }

    StackArrayDouble<int> s2(s);
    int count = 0;

     while (!s.isEmpty()) {
        count++;
        if (s2.pop() != s.pop()) {
            return 0;
        }
    }

    if (count != projectedSize) {
        return 0;
    }
    return 1;
}


int testStackArrayLinearCopyConstructor() {
    StackArrayLinear<int> s;
    int projectedSize = (std::rand() % 25) + 3; 

    for (int i = 0; i < projectedSize; i++) {
        int randomNumber = std::rand() % 100;
        s.push(randomNumber);
    }

    StackArrayLinear<int> s2(s);

     int count = 0;
     while (!s.isEmpty()) {
        count++;
        if (s2.pop() != s.pop()) {
            return 0;
        }
    }

    if (count != projectedSize) {
        return 0;
    }
    return 1;
}


int testStackLinkedListCopyConstructor() {
    StackLinkedList<int> s;
    int projectedSize = (std::rand() % 25) + 3; 

    for (int i = 0; i < projectedSize; i++) {
        int randomNumber = std::rand() % 100;
        s.push(randomNumber);
    }

    StackLinkedList<int> s2(s);

    int count = 0;
    while (!s.isEmpty()) {
        count++;
        if (s2.pop() != s.pop()) {
            return 0;
        }
    }

    if (count != projectedSize) {
        return 0;
    }
    return 1;
}



int testStack(STACK_TYPE stack_type) {
    if (stack_type == STACK_TYPE::ARRAY_DOUBLE) {
        cout << "Running tests for StackArrayDouble:" << endl;
    } else if (stack_type == STACK_TYPE::ARRAY_LINEAR) {
        cout << "Running tests for StackArrayLinear:" << endl;
    } else {
        cout << "Running tests for StackLinkedList:" << endl;
    }

    AbstractStack<int>* s = nullptr;
    int score = 0;

    try {
        s = instantiateStack(stack_type);
        int tscore = testStackEmpty(s);
        if (tscore == 0) {
            cout << "Test Stack Empty Function Failed" << endl;
        } else {
            cout << "Test Stack Empty Function Passed" << endl;
        }
        score += tscore;
        delete s;
    } catch (const std::exception& e) {
        cout << "Test Stack Empty Function Failed" << endl;
        delete s;
    }

    try {
        s = instantiateStack(stack_type);
        int tscore = testStackPush(s);
        if (tscore == 0) {
            cout << "Test Stack Push Function Failed" << endl;
        } else {
            cout << "Test Stack Push Function Passed" << endl;
        }
        score += tscore;
        delete s;
    } catch (const std::exception& e) {
        cout << "Test Stack Push Function Failed" << endl;
        delete s;
    }

    try {
        s = instantiateStack(stack_type);
        int tscore = testStackPop(s);
        if (tscore == 0) {
            cout << "Test Stack Pop Function Failed" << endl;
        } else {
            cout << "Test Stack Pop Function Passed" << endl;
        }
        score += tscore;
        delete s;
    } catch (const std::exception& e) {
        cout << "Test Stack Pop Function Failed" << endl;
        delete s;
    }

    try {
        s = instantiateStack(stack_type);
        int tscore = testStackPop_Exception(s);
        if (tscore == 0) {
            cout << "Test Stack Pop_Exception Function Failed" << endl;
        } else {
            cout << "Test Stack Pop_Exception Function Passed" << endl;
        }
        score += tscore;
        delete s;
    } catch (const std::exception& e) {
        cout << "Test Stack Pop_Exception Function Failed" << endl;
        delete s;
    }

    try {
        s = instantiateStack(stack_type);
        int tscore = testStackTop(s);
        if (tscore == 0) {
            cout << "Test Stack Top Function Failed" << endl;
        } else {
            cout << "Test Stack Top Function Passed" << endl;
        }
        score += tscore;
        delete s;
    } catch (const std::exception& e) {
        cout << "Test Stack Top Function Failed" << endl;
        delete s;
    }

    try {
        s = instantiateStack(stack_type);
        int tscore = testStackTop_Exception(s);
        if (tscore == 0) {
            cout << "Test Stack Top_Exception Function Failed" << endl;
        } else {
            cout << "Test Stack Top_Exception Function Passed" << endl;
        }
        score += tscore;
        delete s;
    } catch (const std::exception& e) {
        cout << "Test Stack Top_Exception Function Failed" << endl;
        delete s;
    }

    return score;
} 



int main() {
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    int finalScore = 0;
    finalScore += testStack(STACK_TYPE::ARRAY_DOUBLE);

    try {
        int tscore = testStackArrayDoubleCopyConstructor();
        if (tscore == 0) {
            cout << "Test Stack Copy Constructor Failed" << endl;
        } else {
            cout << "Test Stack Copy Constructor Passed" << endl;
        }
        finalScore += tscore;
    } catch (const std::exception& e) {
        cout << "Test Stack Copy Constructor Failed" << endl;
    }

    try {
        int tscore = testStackArrayDoubleCopyAssignment();
        if (tscore == 0) {
            cout << "Test Stack Copy Assignment Failed" << endl;
        } else {
            cout << "Test Stack Copy Assignment Passed" << endl;
        }
        finalScore += tscore;
    } catch (const std::exception& e) {
        cout << "Test Stack Copy Constructor Failed" << endl;
    }

    cout << endl;
    finalScore += testStack(STACK_TYPE::ARRAY_LINEAR);

   
    try {
        int tscore = testStackArrayLinearCopyConstructor();
        if (tscore == 0) {
            cout << "Test Stack Copy Constructor Failed" << endl;
        } else {
            cout << "Test Stack Copy Constructor Passed" << endl;
        }
        finalScore += tscore;
    } catch (const std::exception& e) {
        cout << "Test Stack Copy Constructor Failed" << endl;
    }

    
    try {
        int tscore = testStackArrayLinearCopyAssignment();
        if (tscore == 0) {
            cout << "Test Stack Copy Assignment Failed" << endl;
        } else {
            cout << "Test Stack Copy Assignment Passed" << endl;
        }
        finalScore += tscore;
    } catch (const std::exception& e) {
        cout << "Test Stack Copy Constructor Failed" << endl;
    }

    cout << endl;

    int linkedListScore = testStack(STACK_TYPE::LINKED_LIST);


    try {
        int tscore = testStackLinkedListCopyConstructor();
        if (tscore == 0) {
            cout << "Test Stack Copy Constructor Failed" << endl;
        } else {
            cout << "Test Stack Copy Constructor Passed" << endl;
        }
        linkedListScore += tscore;
    } catch (const std::exception& e) {
        cout << "Test Stack Copy Constructor Failed" << endl;
    }

    
    try {
        int tscore = testStackLinkedListCopyAssignment();
        if (tscore == 0) {
            cout << "Test Stack Copy Assignment Failed" << endl;
        } else {
            cout << "Test Stack Copy Assignment Passed" << endl;
        }
        linkedListScore += tscore;
    } catch (const std::exception& e) {
        cout << "Test Stack Copy Constructor Failed" << endl;
    }

    finalScore += 3 * linkedListScore;

    cout << "Your final score is: " << finalScore << " / 50" << endl;
    
    return 0;
}