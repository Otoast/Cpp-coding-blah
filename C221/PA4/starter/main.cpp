#include "AbstractHashTable.h"
#include "ChainingHashTable.h"
#include "ProbingHashTable.h"
#include "DoubleHashTable.h"
#include <chrono>
#include <iostream>
#include <fstream>
#include <unordered_map>
#include <vector>
#include <algorithm> 

#include <random> 
using namespace std;

string generateString(string str){
    string newStr = "";
    bool incNext = true;
    for (int i = 0; i < str.length(); ++i) {
        if (str[i] == 'Z' && i != str.length() - 1) {
            incNext = true;
            newStr.append("A");
        }
        else if (str[i] == 'Z' && i == str.length() - 1) newStr.append("AA");
        else if (incNext){
            newStr += char(str[i] + 1);
            incNext = false;
        }
        else newStr += str[i];
    }
    return newStr;
}


void theNumbersMasonWhatDoTheyMean(vector<string> words){
    cout << "WE ARE ABOUT TO START" << endl;
    vector<int> result;
    ofstream fout;
    fout.open("DoubleHash.csv");
    for(int k=0; k<=15; k++){
        DoubleHashTable cht;
        auto start = chrono::high_resolution_clock::now();
        for(int i=0; i<pow(3,k); i++){    
            cht.insert(words.at(i), rand() % (k * 3/2 + 1));
        }
        auto stop = chrono::high_resolution_clock::now();
        auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);
        result.push_back(duration.count());
    }

    for(int i=0; i<result.size(); i++){
        fout<<pow(3,i) <<","<<result[i]<<endl;
    }
    fout.close();

}
void createDictionary (string filename) {
    std::ofstream file(filename);
    string myStr = "A";
    for (int i = 0; i < 6 * (10000000); ++i){
        myStr = generateString(myStr);
        file << myStr << "\n";
    }

}
int main() {
    
    std::string filename = "dictionary.txt";
    std::ifstream file(filename);
    std::srand(time(NULL));
    if (!file.is_open()) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return 0;
    }

    vector<string> words;
    std::string word;
    while (file >> word) {
        words.push_back(word);
    }
    random_device rd; 
    mt19937 g(rd()); 
    shuffle(words.begin(), words.end(), g); 

    theNumbersMasonWhatDoTheyMean(words);
}




// #include "AbstractHashTable.h"
// #include "ChainingHashTable.h"
// #include "ProbingHashTable.h"
// #include "DoubleHashTable.h"
// #include <string>

// int main() {
//     DoubleHashTable cht;
//     int msize = 30;
//     int c = 20;
//     string key = "A";
//     std::string keys[msize + c];

//     for (int i = 0; i < msize + c; ++i){
//         cht.insert(key, (msize * 31) % (i + 10));
//         keys[i] = key;
//         cout << "Inserted " << key << ": ";
//         cout << cht.get(key) << endl;

//         for (char& c : key) c++;
        
//     }   
//     cout << "Size is: " << cht.getSize() << endl;
//     cout << "Changing A: ";
//     cht.insert("A", 99999);
//     cout << "Inserted A: "  << cht.get("A") << endl;
// }