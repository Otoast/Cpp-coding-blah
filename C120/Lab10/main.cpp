#include "linked_list.h"

using namespace std;

int main(){

    cout << "Creating new linked list..." << endl;
    MyList *l = new MyList();
    cout << "New list creation selection. type y to enter a new node. pres n to end program." << endl;
    char input = ' ';
    cin >> input;
    int score = 0;
    string name = "NODEID_A";
    while (input != 'n'){
        l->add(name, score);
        cout << "Added Node: (" << name << ", " << score << ")" << endl;
        cout << "This is l: " << *l << endl;
        score += 3;
        name += static_cast<char>(65 + score);
        cout << "Would you like to add another node? (y/n)" << endl;
        cin >> input;
    }

    cout << "Ok, about to clear l" << endl;
    delete l;
    cout << "Successfully deleted l." << endl;
 

    return 0;
}