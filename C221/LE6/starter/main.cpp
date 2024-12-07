#include "lru.h"

int main() {
    int msize = 3;
    LRUCache lru (3);

    string key = "A";
    std::string keys[msize];
    
    
    for (int i = 0; i < msize; ++i){
        lru.insertKeyValue(key, i * 2);
        keys[i] = key;
        cout << "Inserted " << key << " most recent key should be it." << endl;
        cout << lru.mostRecentKey() << endl;
        for (char& c : key) c++;
    }
    cout << "Currently, most recent key is: ";
    cout << lru.mostRecentKey() << endl;
    cout << "Value is: " << *(lru.getValue(lru.mostRecentKey())) << endl;

    cout << "Going to get value for key " << keys[0] << endl;
    cout << "Value is: " << *(lru.getValue(keys[0])) << endl;
    
    cout << "Currently, most recent key is: ";
    cout << lru.mostRecentKey() << endl;
    cout << "Value is: " << *(lru.getValue(lru.mostRecentKey())) << endl;

    lru.insertKeyValue("D", 99);
    lru.getValue("B");
    
    

}