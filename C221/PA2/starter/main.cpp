#include <iostream>
#include "deque.h"
using namespace std;


template <class Type>
void checkIntegrity(Deque<Type>& q){
    // return; // Uncomment for skipping prompts
    try{
        cout << "Next line should return something similar to: " << Type() << " | \t"; 
        cout << q.first() << endl;
        cout << "Next line should return something similar to: " << Type() << " | \t"; 
        cout << q.last() << endl;
    }
    catch (...){
        cout << "Bad code." << endl;
    }

    try {
        q.removeFirst();
        cout << "Bad. allows removal" << endl;
    }
    catch(...){
        try{
            q.removeLast();
            cout << "Bad. allows removal" << endl;
        }
        catch(...){
            cout << "Good tried removing items but couldn't. No bad access.\n";
        }
    }
    cout << "Press any key to continue: ";
    
    string promptCheck = "";
    cin >> promptCheck;

    cout << "\n--------------------------------------------------------------------------------------------------------------------------------\n" << endl;


}

template <class Type>
void dequeCheck(Deque<Type>& q){
    // return; // uncomment for skipping prompts

    cout << "Is Deque empty? " << q.isEmpty() << " | what is Deque size? " << q.size() << "\n";
    cout << "Size is: " << q.size() << " | First item: " << q.first() << " Last item: " << q.last() << endl;
    cout << "Press any key to continue: ";
    
    string promptCheck = "";
    cin >> promptCheck;
    
    cout << "\n--------------------------------------------------------------------------------------------------------------------------------\n" << endl;
}

int main(){

    // Master test for deque
    Deque<int> q;
    
    cout << "Is Deque empty? " << q.isEmpty() << " | what is Deque size? " << q.size() << "\n";
    checkIntegrity(q);
    
    cout << "Going to insertLast 10 items. First item should be 1, last item should be 10." << endl;
    for (int i = 1; i <= 10; ++i){
        q.insertLast(i);
    }
    dequeCheck(q);
    

    cout << "Going to insertFirst 10 items. First item should be 100, last item should still be 10\n";
    for (int i = 91; i <=100; ++i){
        q.insertFirst(i);
    }
    dequeCheck(q);

    cout << "Going to pop from front and back 5 times. Both head and tail should be descending\n";
    for (int i = 0; i < 5; ++i){
        cout << "Popped left side: " << q.removeFirst() << "\t";
        cout << "Popped right side: " << q.removeLast() << "\n";
    } 
    cout << "Should be 10 less items now." << endl;
    dequeCheck(q); 

    cout << "Going to now pop everything left to right and reassign new variables." << endl;
    while(!q.isEmpty()){
        cout << "Popped: " << q.removeFirst() << "\n";
    }
    
    cout << "Is Deque empty? " << q.isEmpty() << " | what is Deque size? " << q.size() << "\n";
    checkIntegrity(q);

    cout << "Adding one item: " << endl;
    q.insertFirst(1);
    dequeCheck(q);
    cout << "Adding one more item: " << endl;
    q.insertLast(2); 
    dequeCheck(q);

    cout << "Doing it again in a different matter." << endl;
    while (!q.isEmpty()){
        q.removeFirst();
    }
    q.insertLast(2);
    q.insertFirst(1);
    dequeCheck(q);

    cout << "Making size 100" << endl;
    for (int i = 3; i < 101; ++i){
        q.insertLast(i);
    }
  
    cout << "Making size 5" << endl;
    for (int i = 0; i < 95; ++i){
        q.removeLast();
    }
    dequeCheck(q);

    cout << "Finally, going to check assignment operations. Everything should work as properly.\n";
    Deque<int> r(q);
    cout << "Copy constructored r\n";
    dequeCheck(r);

    Deque<int> s;
    cout << "Inserting s backwards\n";
    s.insertFirst(3);   s.insertFirst(4);   s.insertFirst(5);
    dequeCheck(s);

    s = q;
    cout << "reassigning s\n";
    dequeCheck(s);

    cout << "Popping s from front: \n ";
    while(!s.isEmpty()){
        cout << "Popped: " << s.removeFirst() << "\n";
    }
    dequeCheck(s);

    cout << "If it passes all these tests, deque is probably fine. Now its just for valgrind to tell you if there was memory leaks." << endl;













    
}

// int main() {
//     // Test insertFirst
//     {
//         Deque<int> q;
//         q.insertFirst(3);
//         q.insertFirst(2);
//         q.insertFirst(1);

//         // Now the deque should be [1, 2, 3]
        
//         if (q.size() != 3) {
//             cout << "Test insertFirst failed: Incorrect size" << endl;
            
//         } else if (q.first() != 1 || q.last() != 3) {
//             cout << "Test insertFirst failed: Incorrect elements" << endl;
   
//         } else {
//             cout << "Test insertFirst passed" << endl;
//         }
        
//     }
    
//     // Test insertLast
//     {
//         Deque<int> q;
//         q.insertLast(1);
//         q.insertLast(2);
//         q.insertLast(3);
        
//         // Now the deque should be [1, 2, 3]
        
//         if (q.size() != 3) {
//             cout << "Test insertLast failed: Incorrect size" << endl;
//         } else if (q.first() != 1 || q.last() != 3) {
//             cout << "Test insertLast failed: Incorrect elements" << endl;
//         } else {
//             cout << "Test insertLast passed" << endl;
//         }
        
//     }

//     return 0;
// }