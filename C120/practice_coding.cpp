# include <iostream>
using namespace std;

struct Node {
  int value;
  Node* next;
  Node(int num = 0) : value{num}, next{nullptr} {}
};

class LinkedList {
    public:
    LinkedList() : head{nullptr} {}
    void removeAllMaximum();
    Node* head;

};
ostream& operator<<(ostream& os, const LinkedList& myList) {
    Node* _current = myList.head;
    if (_current == nullptr) {
        os << "<empty>" << endl;
        return os;
    }

    os << "[ "  << _current->value << " ]";
    _current = _current->next;
    while (_current != nullptr) {
        os << " --> [ "  << _current->value << " ]";
        _current = _current->next;
    }
    
    return os;
}

void LinkedList::removeAllMaximum(){

    Node* currNode = head;
    int max = INT32_MIN;
    while (currNode != nullptr){
        if (currNode->value > max){
            max = currNode->value;
        }
        currNode = currNode->next;
    }
    currNode = head;

    // For head exclusive doing
    if (head->value == max){
        Node* tempNode;
        while (currNode != nullptr && currNode->value == max){
            
            tempNode = currNode->next;
            delete currNode;
            
            currNode = tempNode;
            head = currNode;
        }
    }

    currNode = head->next;
    Node* prevNode = head;
    while (currNode != nullptr){
        Node* tempNode = currNode->next;
        
        if (currNode->value == max){
            delete currNode;
            prevNode->next = tempNode;
        }
        else prevNode = prevNode->next;
        // else prevNode = prevNode->next;
        currNode = tempNode;

    }


}

int main(){
    LinkedList l;
    l.head = new Node();
    Node* currNode = l.head;
    cout << currNode->value << endl;
    for (int i = 0; i < 10; ++i){
        int value = 0;
        cin >> value;
        currNode->next = new Node(value);
        currNode = currNode->next;
    }
    cout << l << endl;;
    l.removeAllMaximum();
    
    cout << l << endl;;

    return 0;
}