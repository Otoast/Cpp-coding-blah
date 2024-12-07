#include <iostream>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <algorithm>
#include <vector>
#define TEST
#include "sort.cpp"

using namespace std;

enum SORT_TYPE {
    RADIX_SORT,
    INSERTION_SORT
};

int testSort(SORT_TYPE sort_type, int n) {
    int score = 0;
    int *arr = new int[n];
    vector<int> arrCopy;

    for(int j=0; j<n; j++){
        arr[j] = rand() % 1000000 + 1;  // Random numbers between 1 and 10^6
        arrCopy.push_back(arr[j]);
    }

    sort(arrCopy.begin(), arrCopy.end());
    
    auto start = std::chrono::high_resolution_clock::now();
    if (sort_type == SORT_TYPE::RADIX_SORT) {
       radixSort(arr, n);
    } else if (sort_type == SORT_TYPE::INSERTION_SORT) {
       insertionSort(arr, n);
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
    return 10;
}

int main(){
    srand(time(NULL));

    int finalScore = 0;
   
    try {
        cout << "Testing Radix Sort:" << endl;
        finalScore += testSort(SORT_TYPE::RADIX_SORT, 1000000);

        cout << "Testing Insertion Sort:" << endl;
        finalScore += testSort(SORT_TYPE::INSERTION_SORT, 200000);
    } catch(std::exception& e) {
        cout << e.what() << endl;
    }
    
    cout << "Score: " << finalScore << " / 20" << endl;
    return 0;
}