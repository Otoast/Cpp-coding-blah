#include <iostream>
#include <cassert>
// #include iomanip -- manipulate how data is proccessed by a stream
// sstream & fstream -- string stream and file streams
using namespace std;

int main(){

// output streams write to buffer before console, flushed periodically
// will not flush if program crashes before opportunity to happen
// can manually flush using endl, or cout.flush()

// << operator used to insert data into a stream, can be overloaded by other standard libraries or custom (defining how to print one's own kind of object)
//iomanip library defines special formatting objects, which can be apassed into stream to modify how it prints
    // Ex: setprecision(n), fixed [changes precision to determine number of digits after decimal point]
    // Ex: left, right (alligns left, right text) scientific [sets floats/doubles to pint in scientific notation]



    
}