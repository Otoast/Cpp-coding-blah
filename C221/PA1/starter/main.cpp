#include <iostream>
using namespace std;
#include "AbstractStack.h"
#include "StackArrayDouble.h"
#include "StackArrayLinear.h"
#include "StackLinkedList.h"

int main() {
    StackLinkedList<int> mySLL;
    cout << "Created myStackLinked. Head should be nullptr. Checking if empty: " << mySLL.isEmpty() << "\n";
    cout << "Current Length is: " << mySLL.size() << " Adding items to mySLL:" << endl;
    for (int i = 0; i < 10; ++i){
        mySLL.push(i);
    }
    cout << "New current size is: " << mySLL.size() << " Top item is: " << mySLL.top() << "\n";
    cout << "Going to pop 2 and see what the current item is and length." << endl;
    cout << "1 Pop: " << mySLL.pop() << " 2 Pop: " << mySLL.pop() << "\n";
    cout << "Now new top item is: " << mySLL.top() << " Size is: "<< mySLL.size() << "\n" << endl;
    cout << "Is mySSL empty?: " << mySLL.isEmpty() << "\n";
    cout << "Going to push two more items then ending." << endl;
    mySLL.push(99);
    mySLL.push(100);
    cout << "Done changes. New size is: " << mySLL.size() << " Top item is: " << mySLL.top() << endl;
    cout << "POP 1: " << mySLL.pop() << " New size: " << mySLL.size() << " New Top: " << mySLL.top() << endl;

    while (!mySLL.isEmpty())
    {
        cout <<"About to pop: " << mySLL.pop() << " | Popped." << endl;;
    }
    cout << "Should be cleared. Going to push 10 items again then terminate." << endl;
    for (int i = 91; i < 101; ++i){
        mySLL.push(i);
    }

    return 0;
}