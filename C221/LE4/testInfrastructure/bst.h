#ifndef BST_H
#define BST_H

#include <iostream>
#include <string>

using namespace std;

template <typename Type>
class BST_Node {
public:
    Type key;
    BST_Node* left;
    BST_Node* right;

    BST_Node(Type key) {
        this->key = key;
        this->left = nullptr;
        this->right = nullptr;
    }
};

template <typename Type>
class BST {
private: 
    // helper function for copy constructor
    BST_Node<Type>* copyTree(BST_Node<Type>* originalNode);
    // helper function for deallocating all nodes recursively
    void clearTree(BST_Node<Type>* node);
    // insertRecursive is helper function for insert
    void insertRecursive(BST_Node<Type>* node, Type key);
    // deleteRecursive is helper function for deleteNode
    BST_Node<Type>* deleteRecursive(BST_Node<Type>* node, Type key);
    // Helper method to find the minimum value in the subtree rooted at node (as well as the node itself)
    Type minValue(BST_Node<Type>* node);
    // Helper function for recursively searching for a key
    bool findHelper(BST_Node<Type>* node, Type lkpkey);
    // Helper function for recursively adding the in-order output key values to a string s
    void printTreeInOrderHelper(BST_Node<Type>* node, string& s);
public:
    BST_Node<Type>* root;  
    // Constructor
    BST();
    
    // Copy Constructor
    BST(const BST& other);
    
    // Copy Assignment Operator - uses helper functions copyTree and clearTree
    BST& operator=(const BST& other);

    // Destructor
    ~BST();

    // Insert method to insert node with key
    void insert(Type key);

    // deleteNode method to delete a node with a particular key
    void deleteNode(Type key);

    // Find method to search for a key; returns true if it exists in the tree and false if it does not
    bool find(Type lkpkey);

    // Creates and returns a string that contains the tree in-order
    string printTreeInOrder();
};

template <typename Type>
BST<Type>::BST(){
    this->root = nullptr;
}

template <typename Type>
BST_Node<Type>* BST<Type>::copyTree(BST_Node<Type>* originalNode) {
    if (originalNode == nullptr) return nullptr;
    
    BST_Node<Type>* newNode = new BST_Node<Type>(originalNode->key);
    newNode->left = this->copyTree(originalNode->left);
    newNode->right = this->copyTree(originalNode->right);
    
    return newNode;

}

template <typename Type>
BST<Type>::BST(const BST<Type>& other){
    // Your implementation here
    
    this->root = this->copyTree(other.root);
}

template <typename Type>
BST<Type>& BST<Type>::operator=(const BST& other) {
    if (this == &other) return *this;
    clearTree(root);
    this->root = copyTree(other.root);
    return *this;
}

template <typename Type>
void BST<Type>::clearTree(BST_Node<Type>* node){
    if (node == nullptr) return;
    clearTree(node->left);
    clearTree(node->right);
    delete node;
    node = nullptr;
}

template <typename Type>
BST<Type>::~BST(){
    clearTree(root);
}

template <typename Type>
void BST<Type>::insertRecursive(BST_Node<Type>* node, Type key) {
    if (node->key == key) return;
    
    if (key > node->key){
        if (node->right == nullptr) node->right = new BST_Node<Type>(key);
        else insertRecursive(node->right, key);
    }
    else if (key < node->key){
        if (node->left == nullptr) node->left = new BST_Node<Type>(key);
        else insertRecursive(node->left, key);
    }
    
}

template <typename Type>
void BST<Type>::insert(Type key) {
    if (this->root == nullptr) {
        this->root = new BST_Node<Type>(key);
    } else {
        insertRecursive(this->root, key);
    }
}

template <typename Type>
BST_Node<Type>* BST<Type>::deleteRecursive(BST_Node<Type>* node, Type key) {
    if (node == nullptr) return nullptr;
    else if (node->key != key){
        node->right = deleteRecursive(node->right, key);
        node->left = deleteRecursive(node->left, key);
        return node;
    }
    
    if (node->left != nullptr && node->right != nullptr){
        node->key = minValue(node->right);
        node->right = deleteRecursive(node->right, node->key); 
        return node;
    }
    
    BST_Node<Type>* newNode;
    if (node->left != nullptr) newNode =  node->left;
    else                       newNode = node->right;
    delete node;
    return newNode;
}

template <typename Type>
void BST<Type>::deleteNode(Type key) {
    if (this->root == nullptr) {
        return;
    }
    this->root = deleteRecursive(this->root, key);
}

// Helper method to find the minimum value in the subtree rooted at a particular node (including the node itself)
template <typename Type>
Type BST<Type>::minValue(BST_Node<Type>* node) {
    if (node->left == nullptr && node->right == nullptr){
        return node->key;
    }
    
    Type curr_minValue = node->key;
    if (node->left != nullptr) {
        Type l_minValue = minValue(node->left);
        curr_minValue = (l_minValue < curr_minValue) ? l_minValue : curr_minValue;

    }
    if (node->right != nullptr){
        Type r_minValue = minValue(node->right);
        curr_minValue = (r_minValue < curr_minValue) ? r_minValue : curr_minValue;
    }
    return curr_minValue;
}

template <typename Type>
bool BST<Type>::findHelper(BST_Node<Type>* node, Type lkpkey) {
    if (node == nullptr) return false;
    if (node->key == lkpkey) return true;
    else return (findHelper(node->left, lkpkey) || findHelper(node->right, lkpkey));
}

template <typename Type>
bool BST<Type>::find(Type lpkey) {
    if (this->root == nullptr) {
        return false;
    }
    return findHelper(this->root, lpkey);
}

template <typename Type>
void BST<Type>::printTreeInOrderHelper(BST_Node<Type>* node, string& s) {
    if (node == nullptr) return;
    // if (node->left == nullptr && node->right == nullptr){
    //     s += to_string(node->key) + " ";
    // }
    else {
        printTreeInOrderHelper(node->left, s);
        s += to_string(node->key) + " ";
        printTreeInOrderHelper(node->right, s);
    }

}

template <typename Type>
string BST<Type>::printTreeInOrder() {
    if (this->root == nullptr) {
        return "";
    }
    string s = "";
    printTreeInOrderHelper(this->root, s);
    return s;
}

#endif


