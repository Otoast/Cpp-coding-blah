#include <iostream>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <algorithm>
#include <vector>
#define TEST
#include "merge_sort.cpp"

using namespace std;

enum THREAD_TYPE {
    SINGLE_THREADED,
    MULTI_THREADED
};

int testMergeSort(THREAD_TYPE thread_type, int n) {
    int score = 0;
    int *arr = new int[n];
    vector<int> arrCopy;

    for(int j=0; j<n; j++){
        arr[j] = rand() % 1000000 + 1;  // Random numbers between 1 and 10^6
        arrCopy.push_back(arr[j]);
    }

    sort(arrCopy.begin(), arrCopy.end());
    
    auto start = std::chrono::high_resolution_clock::now();
    if (thread_type == THREAD_TYPE::SINGLE_THREADED) {
       mergeSort(arr, 0, n - 1, 0);
    } else if (thread_type == THREAD_TYPE::MULTI_THREADED) {
       mergeSort(arr, 0, n - 1, 4);
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;
    for(int i=0; i<n; i++){
        if (arrCopy[i] != arr[i]) {
            cout << "Failed" << endl;
            delete[] arr;
            return 0;
        }
    } 

    delete[] arr;
    cout << "Passed" << endl;
    std::cout << "Time taken: " << elapsed.count() << " seconds" << std::endl;
    cout << endl;
    if (thread_type == THREAD_TYPE::SINGLE_THREADED) {
       return 5;
    } else {
       return 15;
    }
}

int main(){
    srand(time(NULL));

    int finalScore = 0;
   
    try {
        cout << "Testing Merge Sort (Single Threaded):" << endl;
        finalScore += testMergeSort(THREAD_TYPE::SINGLE_THREADED, 1000000);

        cout << "Testing Merge Sort (Multi Threaded):" << endl;
        finalScore += testMergeSort(THREAD_TYPE::MULTI_THREADED, 1000000);
    } catch(std::exception& e) {
        cout << e.what() << endl;
    }
    
    cout << "Score: " << finalScore << " / 20" << endl;
    return 0;
}