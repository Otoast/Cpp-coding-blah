#include <iostream>
#include <queue>
using namespace std;

void bubbleSort(int *arr, int size){
    int unsortedSize = size;
    for (unsortedSize; unsortedSize > 0; --unsortedSize) {
        for (int i = 0; i < unsortedSize - 1; ++i) {
            if (arr[i] > arr[i + 1]) {
                int temp = arr[i];
                arr[i] = arr[i + 1];
                arr[i + 1] = temp;
            }      
    
        }
    
    }
}

void heapSort(int *arr, int size){
    priority_queue<int> pq;
    for (int i = 0; i < size; ++i) {
        pq.push(arr[i]);
    }
    for (int i = size - 1; i >= 0; --i) {
        arr[i] = pq.top();
        pq.pop();
    }
}


void mergeSort(int * arr, int start, int end) {
    if (start >= end) return;

    int middle = start + (end - start) / 2;

    mergeSort(arr, start, middle);
    mergeSort(arr, middle + 1, end);    
    
 

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

void quickSort(int *arr, int start, int end) {
    if (start >= end) return;

    int pivot = arr[end];

    int right = end - 1;
    int left = start;
    while (left <= right) {
        if (arr[left] > pivot) {
            if (arr[right] < pivot) {
                int temp = arr[right];
                arr[right] = arr[left];
                arr[left++] = temp;
            }
            else right--;
        }
        else left++;
    }
    int pivotIndex = left;
    arr[end] = arr[pivotIndex];
    arr[pivotIndex] = pivot;

    quickSort(arr, start, pivotIndex - 1);

    quickSort(arr,  pivotIndex + 1, end);
    
}
