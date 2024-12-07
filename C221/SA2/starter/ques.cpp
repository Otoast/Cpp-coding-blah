#include <iostream>

using namespace std;

struct Node {
    int data;
    Node* left;
    Node* right;

    Node(int value) : data(value), left(nullptr), right(nullptr) {}
};

#ifndef ASCENDING_PATHS

// You can create helper functions for count ascending paths if required here

int countAscendingPaths(Node* root){
    int amtAscending = 0;
    Node* leftNextNode = root->left;
    Node* rightNextNode = root->right;
    if (leftNextNode != nullptr) {
        if (leftNextNode->left != nullptr && leftNextNode->left->data > leftNextNode->data || leftNextNode->right != nullptr && leftNextNode->right->data > leftNextNode->data)
            amtAscending += countAscendingPaths(leftNextNode);

        else if (leftNextNode->left == nullptr && leftNextNode->right == nullptr) amtAscending++;

        
    }
    if (rightNextNode != nullptr) {
         if (rightNextNode->left != nullptr && rightNextNode->left->data > rightNextNode->data || rightNextNode->right != nullptr && rightNextNode->right->data > rightNextNode->data)
            amtAscending += countAscendingPaths(rightNextNode);

        else if (rightNextNode->left == nullptr && rightNextNode->right == nullptr) amtAscending++;

        
    }    
    return amtAscending;
}

#endif

#ifndef LEFT_LEAVES

// You can create helper functions for sum of left leaves if required here

int sumOfLeftLeaves(Node* root) {
    int sum = 0;
    Node* leftNode = root->left;
    Node* rightNode = root->right;
    

    if (leftNode != nullptr)  {
        if (leftNode->left != nullptr || leftNode->right != nullptr)
            sum += sumOfLeftLeaves(leftNode);
        else sum += leftNode->data;
    }
    
    if (rightNode != nullptr) 
        if (rightNode->left != nullptr || rightNode->right != nullptr) sum += sumOfLeftLeaves(rightNode);

    
    return sum;

}

#endif

#ifndef TEST_MODE
int main() {
    cout << "Sample Test case 1" << endl;
    
    {
        Node root(3);
        Node left(4), right(5);
        Node leftLeft(7), leftRight(8), rightLeft(9), rightRight(10);
        Node leftRightLeft(3), rightLeftRight(12);

        root.left = &left, root.right = &right;
        left.left = &leftLeft, left.right = &leftRight, right.left = &rightLeft, right.right = &rightRight;
        leftRight.left = &leftRightLeft, rightLeft.right = &rightLeftRight;

        int sumReturned = sumOfLeftLeaves(&root);
        cout << "Testing sum of left leaves" << endl;
        cout << "Expected sum of left leaves: 10" << endl;
        cout << "Returned sum of left leaves: " << sumReturned << endl;

        cout << endl;

        int numAscendingPaths = countAscendingPaths(&root);
        cout << "Testing count ascending paths" << endl;
        cout << "Expected number of ascending paths: 3" << endl;
        cout << "Returned number of ascending paths: " << numAscendingPaths << endl;
    }
    cout << endl;
    cout << endl;

    cout << "Sample Test case 2" << endl;
    {
        Node root(3);
        Node right(4);
        Node rightLeft(5), rightRight(16);
        Node rightRightLeft(14);

        root.right = &right;
        right.left = &rightLeft, right.right = &rightRight;
        rightRight.left = &rightRightLeft;

        int sumReturned = sumOfLeftLeaves(&root);
        cout << "Testing sum of left leaves" << endl;
        cout << "Expected sum of left leaves: 19" << endl;
        cout << "Returned sum of left leaves: " << sumReturned << endl;

        cout << endl;

        int numAscendingPaths = countAscendingPaths(&root);
        cout << "Testing count ascending paths" << endl;
        cout << "Expected number of ascending paths: 1" << endl;
        cout << "Returned number of ascending paths: " << numAscendingPaths << endl;

    }
    cout << "Test sample case 3: " << endl; // Custom test
    {
        Node root (12);
        Node right (4);
        Node left (13);
        Node leftLeft (22);
        Node rightRight (55);
        Node leftRight (99);
        Node rightLeft (102);
        Node leftLeftLeft (12);

        leftLeft.left = &leftLeftLeft;
        left.left = &leftLeft;
        left.right = &leftRight;
        right.left = &rightLeft;
        right.right = &rightRight;
        root.left = &left;
        root.right = &right;
        
        int sumReturned = sumOfLeftLeaves(&root);
        cout << "Testing sum of left leaves" << endl;
        cout << "Expected sum of left leaves: "<< 12 + 102 << endl;
        cout << "Returned sum of left leaves: " << sumReturned << endl;

        cout << endl;

        int numAscendingPaths = countAscendingPaths(&root);
        cout << "Testing count ascending paths" << endl;
        cout << "Expected number of ascending paths: 1" << endl;
        cout << "Returned number of ascending paths: " << numAscendingPaths << endl;


    
    }
    cout << "Test Sample Case 4: " << endl;
    {
        Node root (1);  
        int sumReturned = sumOfLeftLeaves(&root);
        cout << "Testing sum of left leaves" << endl;
        cout << "Expected sum of left leaves: " << 0 << endl;
        cout << "Returned sum of left leaves: " << sumReturned << endl;

        cout << endl;

        int numAscendingPaths = countAscendingPaths(&root);
        cout << "Testing count ascending paths" << endl;
        cout << "Expected number of ascending paths: 0" << endl;
        cout << "Returned number of ascending paths: " << numAscendingPaths << endl;



    }
}
#endif