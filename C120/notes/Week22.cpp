#include <iostream>

using namespace std;


int main(){
const int NUM_ROWS = 3;
const int NUM_COLS = 4;
int arr2d[NUM_ROWS][NUM_COLS];

//Can also be written as      int arr2d[][4] = {{1,2,3,4}, {5,6,7,8}, {9,10,11,12}};
//Most efficient way to traverse a 2d array is 2 nested for loops, row first then colummn

// Alternate way to make an array is with an array of poitners
int row1[1] = {1};
int row2[2] = {2,3};
int row3[3] = {4, 5, 6};
int* arr[3] = {row1, row2, row3};
cout << arr[2][2] << endl;

// Since 1D array can be represented as an int*, we can represent a 2D array as an array of int*, where each int* is a row
// Rows are not adjacent in memory, and is in general slower than a regular 2D array
//BE CAREFUL WITH SCOPE: a variable made in a for loop is tempoary memory. It will be removed once the loop end.

char carString[10];
carString[0] = 'c';
carString[1] = 'a';
carString[2] = 'r';
carString[3] = '\0';
carString[3] = 'z';

for (int i = 0; carString[i] != '\0'; ++i){
    cout << carString[i];
}

/* TYPES OF ERRORS:

Compiler Errors - Program doesn't compile, often because of a syntax error
Runtime Exception - Runnable code, error is made when you run the code
Undefined Behavior - Program does something unexpecred (e.g. accessing memory its not supposed to)
Logic error - Compiles fine, runs fine, but code does not do what you want it to do
Compiler warning - Don't stop your compiler from running, but a sign of an issue 
Bad style - writing ugly */

/* Strategies to find problems:
        Compile frquently
        Read error message - Fix the FIRST error message, then recompile
        Look at line mentioned in error mesage as well as prev. few
        Look up crypric errors

        Rubber Duck Debugging -- explain your code to someone or something, "This is what this code is supposed to do."
        Unit Test (test for a small unit of code)
*/

/*
DEBUGGING PROCESS:
    1) Discover - Realize there exists an error              2) Reproduce - Construct a simple test case that reliably reproduces the error
    3) Isolate - Locate error in code                        4) Fix - Modify code to remove error, verify with testing
    5) Review - Reflect on debugging process
TIPS: 
    - Change only one line at a time
    - Form hypothesis on what is going wrong, test it (eliminate possible causes so you dont spend time considering them)
*/
return 0;


}