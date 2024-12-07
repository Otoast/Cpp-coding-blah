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
    BUBBLE_SORT,
    HEAP_SORT,
    MERGE_SORT,
    QUICK_SORT
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
    if (sort_type == SORT_TYPE::BUBBLE_SORT) {
       bubbleSort(arr, n);
    } else if (sort_type == SORT_TYPE::HEAP_SORT) {
       heapSort(arr, n);
    } else if (sort_type == SORT_TYPE::MERGE_SORT) {
        mergeSort(arr, 0, n - 1);
    } else if (sort_type == SORT_TYPE::QUICK_SORT) {
        quickSort(arr, 0, n - 1);
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
    return 15;
}

int main(){
    srand(time(NULL));

    int finalScore = 0;
   
    try {
        cout << "Testing Bubble Sort:" << endl;
        finalScore += testSort(SORT_TYPE::BUBBLE_SORT, 100000);

        cout << "Testing Heap Sort:" << endl;
        finalScore += testSort(SORT_TYPE::HEAP_SORT, 1000000);

        cout << "Testing Merge Sort:" << endl;
        finalScore += testSort(SORT_TYPE::MERGE_SORT, 1000000);

        cout << "Testing Quick Sort:" << endl;
        finalScore += testSort(SORT_TYPE::QUICK_SORT, 1000000);
    } catch(std::exception& e) {
        cout << e.what() << endl;
    }
    
    cout << "Score: " << finalScore << " / 60" << endl;
    return 0;
}