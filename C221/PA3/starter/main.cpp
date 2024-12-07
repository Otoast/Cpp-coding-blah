#include <iostream>
#include <vector>
#include <chrono>
#include <fstream>
#include <math.h>
#include "UnsortedPriorityQueue.h"
#include "SortedPriorityQueue.h"
#include "PriorityQueueHeap.h"
using namespace std;

void theNumbersMasonWhatDoTheyMean(){

    vector<int> result;
    ofstream fout;
    fout.open("sorteddelete.csv");
    for(int k=0; k<=11; k++){
        SortedPriorityQueue<int> pqh;

         
        auto start = chrono::high_resolution_clock::now();
        for(int i=0; i<pow(3,k); i++){    
        pqh.pq_insert(rand() % (k * 3/2 + 1));
        }
        
        // auto start = chrono::high_resolution_clock::now(); -- For testing deletion/sorting
        // while (pqh.pq_size() != 0){
        //     pqh.pq_delete();
        // }
    
        auto stop = chrono::high_resolution_clock::now();
        auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);
        result.push_back(duration.count());
    }

    for(int i=0; i<result.size(); i++){
        fout<<pow(3,i)<<","<<result[i]<<endl;
    }
    fout.close();

}

int main() {
    theNumbersMasonWhatDoTheyMean();
}