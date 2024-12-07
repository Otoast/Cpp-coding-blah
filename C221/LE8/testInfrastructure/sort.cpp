#include <iostream>
#include "SortedPriorityQueue.h"
#include <vector>
using namespace std;

void radixSort(int *arr, int n) {
    int largestVal = 1;
    for (int i = 0; i < n; ++i) if (arr[i] > largestVal) largestVal = arr[i];
    int biggestExp = 0;   for (int i = largestVal; i != 0; i /= 10) biggestExp++;

    for (int e = 0; e <= biggestExp; e++) {
        int digitPlace = 1; for (int i = 0; i < e; ++i) digitPlace *= 10;
        vector<vector<int>> numbersBucket (10);
        
        for (int indx = 0; indx < n; ++indx) 
            numbersBucket.at(arr[indx] / digitPlace % 10).push_back(arr[indx]);
        
        int arrIndx = 0;
        for (int number = 0; number <= 9; ++number){
            vector<int> bucket = numbersBucket.at(number);
            int bucketSize = bucket.size();
            for (int i = 0; i < bucketSize; ++i) 
                arr[arrIndx++] = bucket.at(i);
            
        }
        


    }
    
    
}


void insertionSort(int *arr, int n) {
    SortedPriorityQueue<int> spq;
    for (int i = 0; i < n; ++i) spq.pq_insert(arr[i]);
    for (int i = 0; i < n; ++i) arr[i] = spq.pq_delete();

}

// 87163 
