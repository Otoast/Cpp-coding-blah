#include <iostream>
#include <vector>
#include <list>
#include <chrono>
#include <fstream>
#include <math.h>

using namespace std;

void insertIntoLinkedList(){
    vector<int> result;
    ofstream fout;
    fout.open("list.csv");
    for(int k=0; k<=6; k++){
        list<int> l;
        auto start = chrono::high_resolution_clock::now();
        for(int i=0; i<pow(10,k); i++){
            l.push_back(i);
        }

        auto stop = chrono::high_resolution_clock::now();
        auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);
        result.push_back(duration.count());
    }

    for(int i=0; i<result.size(); i++){
        fout<<pow(10,i)<<","<<result[i]<<endl;
    }
    fout.close();

}

int main() {
    insertIntoLinkedList();
}