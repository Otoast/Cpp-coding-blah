#define TEST
#include "skiplist.h"
#include <chrono>
#include <algorithm>
using namespace std;

int testSkipListHardCoded(){
    int score = 0;
    int maxLevel = 10;
    double probability = 0.5;
    SkipList skipList(maxLevel, probability);

    skipList.insertElement(3);
    skipList.insertElement(6);
    skipList.insertElement(9);
    skipList.insertElement(2);
    skipList.insertElement(8);
    skipList.insertElement(4);
    skipList.insertElement(5);

    int vec[] = {2, 3, 4, 5, 6, 8, 9};
    for (int i = 0; i < 7; i++) {
        int searchKey = vec[i];
        if (!skipList.searchElement(searchKey)) {
            return 0;
        }
    }
    
    cout << "Insert passed in hardcoded skip list" << endl;
    score = 5;
    
    int deleteOrder[] = {3, 6, 9, 2, 8, 4, 5};
    for (int i = 0; i < 7; i++) {
        int deleteKey = deleteOrder[i];
        skipList.deleteElement(deleteKey);
        if (skipList.searchElement(deleteKey)) {
            return score;
        }
        for (int j = i + 1; j < 7; j++) {
            if (!skipList.searchElement(deleteOrder[j])) {
                return score;
            }
        }
    }

    cout << "Delete passed in hardcoded skip list" << endl;
    score += 5;
    return score;
}

  
int testSkipListRandom() {
    int maxLevel = 10;
    double probability = 0.5;
    SkipList skipList(maxLevel, probability);

    int n = 100000;
    srand(time(0));
    vector<int> v;

    std::chrono::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < n; i++) {
        int r = rand() % 10;
        if (r < 4) { // insert 
            int x = rand() % 1000000;
            skipList.insertElement(x);
            v.push_back(x);
            
            bool found = skipList.searchElement(x);
            if (found == false) {
                return 0;
            }
        } else if (r < 8) { // search
            if (v.size() > 0) {
                int r = rand() % v.size();
                bool found = skipList.searchElement(v[r]);
                if (found == false) {
                    return 0;
                }
            }
        } 
        else { // delete
            if (v.size() > 0) {
                int r = rand() % v.size();
                int x = v[r];
                bool found = skipList.searchElement(x);
                if (found == false) {
                    return 0;
                }

                skipList.deleteElement(x);
                v.erase(std::remove(v.begin(), v.end(), x), v.end());
                
                found = skipList.searchElement(x);
                if (found == true) {
                    return 0;
                }
            }
        }
    }
    std::chrono::high_resolution_clock::time_point end = std::chrono::high_resolution_clock::now();
    std::chrono::milliseconds duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    for (int i = 0; i < v.size(); i++) {
        if (!skipList.searchElement(v[i])) {
            return 0;
        }
    }
    cout << "DURATION for random simulation: " << duration.count() << " milliseconds" << endl;
    return 10;
}

int main() {
    int score = 0; 
    try {
        int temp_score = 0;
        temp_score = testSkipListHardCoded();
        if (temp_score == 0) {
            cout << "Hard coded skip list test failed" << endl;
        } else {
            cout << "Hard coded skip list test passed" << endl;
        }
        cout << endl;
        score += temp_score;
        temp_score = testSkipListRandom();
        if (temp_score == 0) {
            cout << "Random skip list test failed" << endl;
        } else {
            cout << "Random skip list test passed" << endl;
        }
        score += temp_score;
        cout << endl;
    } catch(std::exception& e) {
        cout << e.what() << endl;
    }

    cout << "Score: " << score << " / 20" << endl;
    return 0;
}