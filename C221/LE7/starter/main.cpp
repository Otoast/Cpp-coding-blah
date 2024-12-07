#include "skiplist.h"

int main() {
    SkipList sl (9, .5);

    sl.displayList();
    sl.insertElement(22);
    sl.displayList();
    sl.insertElement(33);
    sl.displayList();
    sl.insertElement(44);
    sl.displayList();
    sl.insertElement(44);
    sl.insertElement(19);
    sl.insertElement(40);
    sl.insertElement(12);
    sl.insertElement(49);
    sl.insertElement(0);
    sl.displayList();

    cout << "IS 22 in the tingy or whatever? " << sl.searchElement(22);
    cout << "DELETING 12" << endl;
    try {
        sl.deleteElement(1);
    }
    catch (std::runtime_error) {
        cout << "NICE didnt delete element not at da list" << endl;
    }
    sl.deleteElement(12);
    sl.displayList();
}