#include <iostream>
#include <vector>
#include <chrono>
#include <cstdlib>
#include <algorithm>

using namespace std;

bool PLOT_GRAPH = true;

void plotBarGraph(const vector<double>& data, const vector<int>& n) {
    int maxValue = *max_element(data.begin(), data.end());

    for (int i = 0; i < data.size(); i++) {
        int barLength = static_cast<int>(data[i] * 80 / maxValue); // Scale the bar length
        if(i==data.size()/2){
            cout << "n " << n[i] << "\t |";
        }else{
            cout << "  " << n[i] << "\t |";
        }
        for (int j = 0; j < barLength; j++) {
            cout << "*";
        }
        cout << " (" << data[i] << ")\n";
    }
}

int algo1(vector<int>& lis_arr, int target) {
    int n = lis_arr.size();
    int count = 0;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (lis_arr[i] + lis_arr[j] == target) {
                count++;
            }
        }
    }
    return count;
}

void measureAlgo1(){
    vector<double> algo1_time;
    vector<int> datapoints1;

    for (int i = 1; i < 10000; i += 100) {
        datapoints1.push_back(i);
    }
    
    cout<<"algo1 (measured in microseconds)"<<endl;
    
    for (int i = 0; i < datapoints1.size(); i++) {
        vector<int> x;
        for (int j = 0; j < datapoints1[i]; j++) {
            x.push_back(rand() % 100 + 1);
        }
        auto start = chrono::high_resolution_clock::now();
        algo1(x, rand() % 200 + 1);
        auto stop = chrono::high_resolution_clock::now();
        auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);
        algo1_time.push_back(duration.count());
    }
    if(PLOT_GRAPH) plotBarGraph( algo1_time, datapoints1);
}

int algo2(int n) {
    if (n == 1 || n == 2) {
        return 1;
    }
    if (n > 2) {
        return algo2(n - 1) + algo2(n - 2);
    }
    return -1;
}

void measureAlgo2(){
    // Measuring time for algo2
    vector<double> algo2_time;
    vector<int> datapoints2;
    for (int i = 0; i <= 43; i++) {
        datapoints2.push_back(i);
    }
    
    cout<<"algo2 (measured in microseconds)"<<endl;
    
    for (int i = 0; i < datapoints2.size(); i++) {
        auto start = chrono::high_resolution_clock::now();
        algo2(datapoints2[i]);
        auto stop = chrono::high_resolution_clock::now();
        auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);
        algo2_time.push_back(duration.count());
    }
    if(PLOT_GRAPH) plotBarGraph( algo2_time, datapoints2);
}


int algo3(const vector<int>& lis_arr, int target, int low = 0, int high = -1) {
    if (high == -1) {
        high = lis_arr.size() - 1;
    }

    if (high < low) {
        return -1;
    }

    int midpoint = (low + high) / 2;

    if (lis_arr[midpoint] == target) {
        return midpoint;
    } else if (target < lis_arr[midpoint]) {
        return algo3(lis_arr, target, low, midpoint - 1);
    } else {
        return algo3(lis_arr, target, midpoint + 1, high);
    }
}

void measeureAlgo3(){
    // Measuring time for algo3
    vector<double> algo3_time;
    vector<int> datapoints3;

    cout<<"algo3 (measured in nanoseconds)"<<endl;
    
    for (int i = 1; i < 100000; i += 1000) {
        datapoints3.push_back(i);
    }

    for (int i = 0; i < datapoints3.size(); i++) {
        vector<int> x;
        for (int j = 0; j < datapoints3[i]; j++) {
            x.push_back(j);
        }
        auto start = chrono::high_resolution_clock::now();
        algo3(x, 45600);
        auto stop = chrono::high_resolution_clock::now();
        auto duration = chrono::duration_cast<chrono::nanoseconds>(stop - start);
        algo3_time.push_back(duration.count());
    }
    if(PLOT_GRAPH) plotBarGraph( algo3_time, datapoints3);
}

int algo4(const vector<int>& lis_arr, int target) {
    for (int i = 0; i < lis_arr.size(); i++) {
        if (lis_arr[i] == target) {
            return i;
        }
    }
    return -1;
}

void measeureAlgo4(){
    // Measuring time for algo4
    vector<double> algo4_time;
    vector<int> datapoints4;
    cout<<"algo4 (measured in microseconds)"<<endl;

    for (int i = 1; i < 10000; i += 100) {
        datapoints4.push_back(i);
    }

    for (int i = 0; i < datapoints4.size(); i++) {
        vector<int> x;
        for (int j = 0; j < datapoints4[i]; j++) {
            x.push_back(rand() % 100 + 1);
        }
        auto start = chrono::high_resolution_clock::now();
        algo4(x, 785);
        auto stop = chrono::high_resolution_clock::now();
        auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);
        algo4_time.push_back(duration.count());
    }
    if(PLOT_GRAPH) plotBarGraph( algo4_time, datapoints4);
}


int algo5helper(int base, int exponent) {
    if (exponent == 0) {
        return 1;
    } else if (exponent % 2 == 0) {
        int half_power = algo5helper(base, exponent / 2);
        return half_power * half_power;
    } else {
        return base * algo5helper(base, exponent - 1);
    }
}

vector<int> algo5(vector<int>& lis_arr) {
   int n = lis_arr.size();
   vector<int> powers(n);
   for (int i = 0; i < n; i++) {
        int base = lis_arr[i];
        int exponent = 11;
        int power = algo5helper(lis_arr[i], exponent);
        powers[i] = power;
   }
   return powers;
}

void measureAlgo5(){
    // Measuring time for algo5
    vector<double> algo5_time;
    vector<int> datapoints5;
    cout<<"algo5 (measured in microseconds)"<<endl;

    for (int i = 1; i < 10000; i += 100) {
        datapoints5.push_back(i);
    }

    for (int i = 0; i < datapoints5.size(); i++) {
        vector<int> x;
        for (int j = 0; j < datapoints5[i]; j++) {
            x.push_back(rand() % 5 + 2);
        }
        auto start = chrono::high_resolution_clock::now();
        algo5(x);
        auto stop = chrono::high_resolution_clock::now();
        auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);
        algo5_time.push_back(duration.count());
    }

    if(PLOT_GRAPH) plotBarGraph( algo5_time, datapoints5);
}


int main() {
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    cout<<"To plot graph set PLOT_GRAPH = true"<<endl;
    cout << " " << endl;
    measureAlgo1(); 
    for (int i = 0; i < 3; i++) {
        cout <<  " " << endl;
    }
    measureAlgo2();
    for (int i = 0; i < 3; i++) {
        cout <<  " " << endl;
    }
    measeureAlgo3();
    for (int i = 0; i < 3; i++) {
        cout <<  " " << endl;
    }
    measeureAlgo4();
    for (int i = 0; i < 3; i++) {
        cout <<  " " << endl;
    }
    measureAlgo5();

    return 0;
}
