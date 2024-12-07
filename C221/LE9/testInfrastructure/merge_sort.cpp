#include <iostream>
#include <thread>
using namespace std;

void mergeSort(int * arr, int start, int end, int level) {
    if (start >= end) return;

    int middle = start + (end - start) / 2;
    if (level > 0) {
        thread t1 (mergeSort, arr, start, middle, level - 1);
        thread t2 (mergeSort, arr, middle + 1, end, level - 1);

        t1.join();
        t2.join();
    }
    else {
        mergeSort(arr, start, middle, level - 1);
        mergeSort(arr, middle + 1, end, level - 1);
    }

 int* tempArr = new int[end - start + 1];
    int tempIndex = 0;  int rightIndex = middle + 1; int leftIndex = start;
    while (rightIndex <= end && leftIndex <= middle) {
        if (arr[leftIndex] < arr[rightIndex]) tempArr[tempIndex++] = arr[leftIndex++];
        else                                  tempArr[tempIndex++] = arr[rightIndex++]; 
    }
    while (leftIndex <= middle) tempArr[tempIndex++] = arr[leftIndex++];
    while (rightIndex <= end) tempArr[tempIndex++] = arr[rightIndex++];

    tempIndex = 0;
    for (int i = start; i <= end; ++i) 
        arr[i] = tempArr[tempIndex++];
    
    delete [] tempArr;


}