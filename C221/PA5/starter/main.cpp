#include <iostream>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <algorithm>
#include <vector>
#define TEST
#include "sort.cpp"
#include <fstream>
#include <math.h>
using namespace std;

enum SORT_TYPE {
    BUBBLE_SORT,
    HEAP_SORT,
    MERGE_SORT,
    QUICK_SORT
};

void testSort() {
    int size = 100;
    int *arr = new int[size];
        for(int j=0; j< size; j++){
            arr[j] = rand() % 100 + 1;  // Random numbers between 1 and 10^6
        }
    mergeSort(arr, 0, size - 1);
    for (int i = 0; i < size; ++i) cout << arr[i] << " ";
    delete [] arr;
}

int main(){
   
   testSort();

    return 0;
}