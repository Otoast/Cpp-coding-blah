#include "sort.cpp"

int main() {
    // int n = 40;
    // int *arr = new int[n];
    // vector<int> arrCopy;

    // for(int j=0; j<n; j++){
    //     arr[j] = rand() % 1000000 + 1;  // Random numbers between 1 and 10^6
    //     arrCopy.push_back(arr[j]);
    // }
    int arr[10] = {9, 37, 79, 52, 18, 94, 11, 73, 31, 60};
    int n = 10;
    insertionSort(arr, n);
    cout << "Insertion sort finished" << endl;
    for (int i = 0; i < n; ++i) 
        cout << arr[i] << " ";
}