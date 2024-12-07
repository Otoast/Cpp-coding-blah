#define TEST
#include "bst.h"
#include <vector>    
#include <random>    
#include <cstdlib>
#include <ctime>   
#include <iostream>
#include <queue>
#include <tuple>
#include <algorithm>
using namespace std;

#define DEBUG 0

int levelOrderPrint(BST<int>* bst) {
    int count = 0;

    if (DEBUG) {
        cout << "LEVEL ORDER PRINT" << endl;
    }

    if (bst->root == nullptr) {
        if (DEBUG) {
            cout << "BST Empty" << endl;
            cout << endl;
        }
        
        return 0;
    }

    queue<BST_Node<int>*> q;
    q.push(bst->root);
    q.push(nullptr);
    
    while (!q.empty()) {
        BST_Node<int>* curr = q.front();
        q.pop();

        if(curr == nullptr) {
            if (!q.empty()) {
                q.push(nullptr);
            }
            if (DEBUG) {
                cout << endl;
            }
            continue;
        }

        if (DEBUG) {
            cout << curr->key<< "\t";
        }
        
        count++;
        if(curr->left!=nullptr){
            q.push(curr->left);
        }
        if(curr->right!=nullptr){
            q.push(curr->right);
        }
    }

    if (DEBUG) {
        cout << endl;
        cout << endl;
    }

    
    return count;
}

bool isBSTValid(BST_Node<int>* node, BST_Node<int>* left = nullptr, BST_Node<int>* right = nullptr) {
    if (node == nullptr) 
        return true;

    if (left != nullptr && node->key <= left->key) 
        return false;

    if (right != nullptr && node->key >= right->key) 
        return false;

    return isBSTValid(node->left, left, node) && 
        isBSTValid(node->right, node, right);
}

bool isValidBST(BST<int>* bst) {
    return isBSTValid(bst->root, nullptr, nullptr);
}

void insertMiddle(BST<int>* bst, const std::vector<int>& values, int start, int end) {
    if (start > end) return; 
    int mid = start + (end - start) / 2;
    bst->insert(values[mid]); 
    insertMiddle(bst, values, start, mid - 1);
    insertMiddle(bst, values, mid + 1, end);
}

int testInsert(BST<int>* bst, int n){
    std::vector<int> values(n);
    for (int i = 0; i < n; ++i) {
        values[i] = i + 1; 
    }
    insertMiddle(bst, values, 0, n - 1);

    int count = levelOrderPrint(bst);
    if (count != n) {
        return 0;
    }

    for (int i = 0; i < n; ++i) {
        if (!bst->find(i + 1)) {
            return 0;
        }
    }

    if (!isValidBST(bst)) {
        return 0;
    }
   
    return 5;
}

int testFind(BST<int>* bst, int n){
    std::vector<int> elements(2 * n);
    for(int i = 0; i < 2 * n; ++i) {
        elements[i] = i + 1;
    }
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(elements.begin(), elements.end(), g);
    for (int i = 0; i < n; ++i) {
        bool found = bst->find(elements[i]);
        if (elements[i] <= n && found == false) {
            return 0;
        } else if (elements[i] > n && found == true) {
            return 0;
        }
    }
    return 2;
}

int testDelete(BST<int>* bst, int n){
    int count = levelOrderPrint(bst);
    if (count != n) {
        cout << "You have not passed insert; pass insert before you test delete!" << endl;
        return 0;
    }

    for (int i = 0; i < n; ++i) {
        if (!bst->find(i + 1)) {
            cout << "You have not passed insert or find; pass insert and find before you test delete!" << endl;
            return 0;
        }
    }

    if (!isValidBST(bst)) {
        cout << "You have not passed insert; pass insert before you test delete!" << endl;
        return 0;
    }

    if (bst->find(2 * n)) {
        cout << "You have not passed insert or find; pass insert and find before you test delete!" << endl;
        return 0;
    }

    std::vector<int> elements(n);
    for(int i = 0; i < n; ++i) {
        elements[i] = i + 1;
    }

    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(elements.begin(), elements.end(), g);

    for (int i = 0; i < n; ++i) {
        bst->deleteNode(elements[i]);
        bool found = bst->find(elements[i]);
        if (!isValidBST(bst) || found) {
            return 0;
        }
        int curSize = levelOrderPrint(bst);
        if (curSize != n - i - 1) {
            return 0;
        }
    }

    return 7;
}

int testPrintInOrder(BST<int>* bst, int n) {
    string actualInOrder = bst->printTreeInOrder();
    string expectedInOrder = "";
    for (int i = 0; i < n; i++) {
        expectedInOrder += to_string(i + 1) + " ";
    }
    if (actualInOrder != expectedInOrder && actualInOrder != expectedInOrder.substr(0, expectedInOrder.size() - 1)) {
        return 0;
    }
    return 2;
}

int testCopyConstructor(int n) {
    std::vector<int> values(n);
    for (int i = 0; i < n; ++i) {
        values[i] = i + 1; 
    }
    
    BST<int>* bst = new BST<int>();
    insertMiddle(bst, values, 0, n - 1);

    BST<int>* bst2 = new BST<int>(*bst);
    int count2 = levelOrderPrint(bst2);

    if (count2 != n) {
        return 0;
    } 

    for (int i = 0; i < n; ++i) {
        if (!bst2->find(i + 1)) {
            return 0;
        }
    }

    if (!isValidBST(bst2)) {
        return 0;
    }


    bst->insert(n * 10);
    if (bst2->find(n * 10)) {
        return 0;
    }
    bst->deleteNode(n * 10);

    std::vector<int> elements(n);
    for(int i = 0; i < n; ++i) {
        elements[i] = i + 1;
    }

    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(elements.begin(), elements.end(), g);

    for (int i = 0; i < n; ++i) {
        bst2->deleteNode(elements[i]);
        bool found = bst2->find(elements[i]);
        if (!isValidBST(bst2) || found) {
            return 0;
        }
        int bstCount = levelOrderPrint(bst);
        if (bstCount != n) {
            return 0;
        }
        if (!bst->find(elements[i])) {
            return 0;
        }
    }

    delete bst;
    delete bst2;

    return 2;
}

int testCopyAssignment(int n) {
    std::vector<int> values(n);
    for (int i = 0; i < n; ++i) {
        values[i] = i + 1; 
    }
    
    BST<int> bst;
    insertMiddle(&bst, values, 0, n - 1);

    BST<int> bst2;
    for (int i = 2 * n; i < 4 * n; i++) {
        bst2.insert(i + 1);
    }

    bst2 = bst;

    bst.insert(n * 10);
    if (bst2.find(n * 10)) {
        return 0;
    }
    bst.deleteNode(n * 10);

    int count2 = levelOrderPrint(&bst2);
    if (count2 != n) {
        return 0;
    } 

    for (int i = 0; i < n; ++i) {
        if (!bst2.find(i + 1)) {
            return 0;
        }
    }

    if (!isValidBST(&bst2)) {
        return 0;
    }

    std::vector<int> elements(n);
    for(int i = 0; i < n; ++i) {
        elements[i] = i + 1;
    }

    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(elements.begin(), elements.end(), g);

    for (int i = 0; i < n; ++i) {
        bst2.deleteNode(elements[i]);
        bool found = bst2.find(elements[i]);
        if (!isValidBST(&bst2) || found) {
            return 0;
        }
        int bstCount = levelOrderPrint(&bst);
        if (bstCount != n) {
            return 0;
        }
        if (!bst.find(elements[i])) {
            return 0;
        }
    }

    return 2;
}

int main() {
    std::srand(std::time(0));
    int n = rand() % 50 + 41;

    BST<int>* bst = new BST<int>();
    int score = 0;
    try {
        int temp_score = testInsert(bst, n);
        if (temp_score == 0) {
            cout << "TEST INSERT FAILED" << endl;
        } else {
            cout << "TEST INSERT PASSED" << endl;
        }
        score += temp_score;

        temp_score = testFind(bst, n);
        if (temp_score == 0) {
            cout << "TEST FIND FAILED" << endl;
        } else {
            cout << "TEST FIND PASSED" << endl;
        }
        score += temp_score;

        temp_score = testPrintInOrder(bst, n);
        if (temp_score == 0) {
            cout << "TEST PRINT IN ORDER FAILED" << endl;
        } else {
            cout << "TEST PRINT IN ORDER PASSED" << endl;
        }
        score += temp_score;

        temp_score = testDelete(bst, n);
        if (temp_score == 0) {
            cout << "TEST DELETE FAILED" << endl;
        } else {
            cout << "TEST DELETE PASSED" << endl;
        }
        score += temp_score;

        temp_score = testCopyConstructor(n);
        if (temp_score == 0) {
            cout << "TEST COPY CONSTRUCTOR FAILED" << endl;
        } else {
            cout << "TEST COPY CONSTRUCTOR PASSED" << endl;
        }
        score += temp_score;

        temp_score = testCopyAssignment(n);
        if (temp_score == 0) {
            cout << "TEST COPY ASSIGNMENT FAILED" << endl;
        } else {
            cout << "TEST COPY ASSIGNMENT PASSED" << endl;
        }
        score += temp_score;
    } catch(std::exception& e) {
        cout << e.what() << endl;
    }
    
    cout<< "Score: " << score << " / 20" << endl;
    delete bst;
    return 0;
}   