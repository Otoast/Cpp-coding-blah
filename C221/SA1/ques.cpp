#include <iostream>
#include <string>
using namespace std;

template <typename T>
class Node {
public:
    T data;
    Node<T>* prev;
    Node<T>* next;

    Node(T val) : data(val), prev(nullptr), next(nullptr) {}
};

template <typename T>
class DoublyLinkedList {
private:
    Node<T>* head;
    Node<T>* tail;
    int size;

public:
    DoublyLinkedList() : head(nullptr), tail(nullptr), size(0) {}

    ~DoublyLinkedList() {
        Node<T>* current = head;
        while (current != nullptr) {
            Node<T>* temp = current->next;
            current->next = nullptr;
            current->prev = nullptr;
            delete current;
            current = temp;
        }
        tail = nullptr;
        head = nullptr;
    }

    // inserts element to end of list
    void append(T data) {
        Node<T>* newNode = new Node<T>(data);
        if (head == nullptr) {
            head = newNode;
            tail = newNode;
        } else {
            newNode->prev = tail;
            tail->next = newNode;
            tail = newNode;
        }
        size++;
    }

    string display() {
        Node<T>* current = head;
        string displayStr = "";
        while (current) {
            displayStr += to_string(current->data);
            current = current->next;
            if (current != nullptr) {
                displayStr += " <-> ";
            }
        }
        return displayStr;
    }

    bool isPalindromic() {
        if (size == 0 || size == 1) return true;
       bool palindrome = true;
       Node<T>* frontNode = head;
       Node<T>* backNode = tail;
       while (frontNode != nullptr && backNode != nullptr && frontNode != backNode){
        if (frontNode->data != backNode->data) palindrome = false;
        frontNode = frontNode->next;
        backNode = backNode->prev;
       }
       return palindrome;
    }

    /*
    // Consider the first node in the list to be at position 1
    // Consider the second node in the list to be at position 2 and so on
    // Positions can range from 1 to x (where x = size)

    // You must swap the data of an even positioned node with its preceding odd positioned node
        // For example you must swap 
            // node 2's data with node 1's data
            // node 4's data with node 3's data
        // If the doubly linked list has odd number of nodes, then the last node will be left as is (as it does not have a succeeding even positioned node to swap with)
    */
    void swapAtEvenPosition() {
        Node<T>* oddNode = head;
        Node<T>* evenNode = head->next;
        while (evenNode != nullptr && oddNode != nullptr){
            T oddData = oddNode->data;
            oddNode->data = evenNode->data;
            evenNode->data = oddData;
            
            evenNode = evenNode->next;
            oddNode = oddNode->next;
            if (evenNode != nullptr){
                evenNode = evenNode->next;
                oddNode = oddNode->next;
            }
        }
    }
};

#ifndef TEST_MODE
int main() {
    cout << "Testing isPalindromic" << endl;
    cout << endl;
    {
        {
            DoublyLinkedList<int> dll;
            dll.append(1);
            dll.append(2);
            dll.append(3);
            dll.append(2);
            dll.append(1);

            std::cout << "Doubly Linked List:" << std::endl;
            cout << dll.display() << endl;

            // should be palindromic
            std::cout << "Is Palindromic: " << (dll.isPalindromic() ? "true" : "false") << std::endl;
            cout << endl;
        }

        {
            DoublyLinkedList<int> dll2;
            dll2.append(1);
            dll2.append(2);
            dll2.append(3);
            dll2.append(2);
            dll2.append(2);

            std::cout << "Doubly Linked List:" << std::endl;
            cout << dll2.display() << endl;

            // should not be palindromic
            std::cout << "Is Palindromic: " << (dll2.isPalindromic() ? "true" : "false") << std::endl;
            cout << endl;
        }

        {
            DoublyLinkedList<int> dll3;
            dll3.append(1);
            dll3.append(2);
            dll3.append(2);
            dll3.append(1);

            std::cout << "Doubly Linked List:" << std::endl;
            cout << dll3.display() << endl;
            
            // should be palindromic
            std::cout << "Is Palindromic: " << (dll3.isPalindromic() ? "true" : "false") << std::endl;
            cout << endl;
        }
    }

    cout << endl;
    cout << endl;

    cout << "Testing swapAtEvenPosition" << endl;
    cout << endl;

    {
        {
            DoublyLinkedList<int> dll;
            dll.append(15);
            dll.append(9);
            dll.append(5);
            dll.append(12);
            dll.append(7);

            std::cout << "Doubly Linked List Before Swapping:" << std::endl;
            cout << dll.display() << endl;

            dll.swapAtEvenPosition();
            
            // Expected: 9 15 12 5 7
            std::cout << "Doubly Linked List After Swapping:" << std::endl;
            cout << dll.display() << endl;
            cout << endl;
        }

        {
            DoublyLinkedList<int> dll2;
            dll2.append(21);
            dll2.append(8);
            dll2.append(52);
            dll2.append(6);

            std::cout << "Doubly Linked List Before Swapping:" << std::endl;
            cout << dll2.display() << endl;

            dll2.swapAtEvenPosition();
            
            // Expected: 8 21 6 52
            std::cout << "Doubly Linked List After Swapping:" << std::endl;
            cout << dll2.display() << endl;
        }

    }


    return 0;
}
#endif
