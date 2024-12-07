#include <iostream>

using namespace std;


int main(){

//Primitive data type: built into C++, stores single piece of info (ex: int, char)
// Aggregate data type: Combines other data types (ex: array, Class)

struct Point{
    double x;
    double y;
}; //Notice semicolon at end: used to group several related variables to single data type

Point p; // Think like creating an object with multiple values inside
p.x = 7; p.y = 10; //Two ways to initialize
Point q = {5, 2};
// For custom data types, you have to specify how you want cout to print

//Arrays -- used to group variables of same type
// the size of an array must be specified when we define it, must be constant
int squares[10];
for (int i = 0; i < 10; i++){
    squares[i] = i*i;
}
//Missing values are initialized to a default value of 0
int triangles[10] = {};
int circles[10] = {0, 1, 4, 9};
/*Because arrays are rigid in size during runtime, the best workaround is to
allocate more space than you really need, and keep track of elemeents, array size, etc.*/

std::cout << squares; //prints memory address

//Can combine arrays and structs
Point pointArr[3] = {{1, 2}, {4, 7}, {-3, 12}};




    // Variable which represents an address (location) in the computr memory
    // Pointer points ot a specific type of value
    int* ptr = nullptr; //Use nullptr to avoid having undefined behavior

    int x = 120;
    ptr = &x; //"Address of" operator
    cout << ptr << endl; //Prints address
    cout << *ptr << endl; // derefrences the pointer, gets the value stored

    int arr[] = {1, 2, 4, 4, 5};
    int *arr2 = arr; //Arrays can be cast to pointers of corresponding type (pointer to first element of array)
    /*Arrays (such as an int array) work by pointing towards the first element in an array--
        it then adds the size of an int to the memory address to iterate to the next value.
        if you send an struct to a function, it will send a copy of the array to the function, while--
        if you send an array to a function, it will send a refrence (memory address) to the function (and depends on the user to remember the array size) while--
        if you send the pointer, it sends a copy of the memory address of the array (which is the actual array holding the value).*/

    const int xz = 7; // creates a variable that can't be modified

    /*Two types of strings-- one focused on rn is "C-style strings"

    essentially are char arrays, terminated by a null terminator */
    char str[] = "hello";
    cout << sizeof(str) << endl;

//------------------------------------------------------------------------------------------9/1----------------------------------------------------------------------------------

//Passing by value: function being called gets new copy of date (Used for primitive types and structs)
//Passing by reference: Function being called gets pointer to original coppy of data (used for arrays and any type passed by pointer)


}
