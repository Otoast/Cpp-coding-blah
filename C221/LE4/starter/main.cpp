#include "bst.h"
using namespace std;

#ifndef TEST
int main() {
    
    BST<int>* t = new BST<int>();
    
    t->insert(1);
    t->insert(9);
    t->insert(4);
    t->insert(2);
    t->insert(5);
    t->insert(8);
    t->insert(3);
    t->insert(5);
    t->insert(7);
    t->insert(10);
    t->insert(6);

    BST<int>* s = new BST<int>(*t);
    cout << (t->printTreeInOrder()) << endl;
    delete t; 
    cout << s->printTreeInOrder() << endl;
    s->deleteNode(5);
    s->deleteNode(9);
    s->deleteNode(1);
    s->deleteNode(4);
    cout << s->printTreeInOrder() << endl;
    


    delete s;
    




    return 0;
}
#endif