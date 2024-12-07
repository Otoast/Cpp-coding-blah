#include <iostream>
#include <vector>
#include <chrono>
#include <fstream>
#include <math.h>

using namespace std;

void insertIntoVector(){

    vector<int> result;
    ofstream fout;
    fout.open("vector.csv");
    for(int k=0; k<=6; k++){
        vector<int> v;
        auto start = chrono::high_resolution_clock::now();
        for(int i=0; i<pow(10,k); i++){
            v.push_back(i);
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
    insertIntoVector();
}