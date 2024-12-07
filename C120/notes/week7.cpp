#include <iostream>
using namespace std;
int main(){
int x = 69420;
int &y = x; //y is a reference. It is essentially another name for x
int *w = &x; //y is a pointer. It holds the memory address of x. Can be assigned to a new memory address
// Each object has its own special type of pointer, can be uninitialized. References cannot be uninitialized

/* Using references over pointers is generally prefered When pointers are neccesary
    (1) Change memory address of variable
    (2) Need a variable to refer to no memory address at all (null pointer) 
    (3) Need to use functions written in C-style
    (4) Pointers are backwards compatible with C, references are not.
*/
// References are useful for function passing by reference without performing too much extra syntax
// variable decalred as const reference cannot be assigned to aftr initialization, essentially "promise" compiler you wont do anything
//      only to pass literal by reference, like sort(120) and int sort(const int& x)

/* When to pass by reference:
        -->If function needs to modify its input argument
    When to pass by const reference:
        -->When input is large and doesnt need to be copied
        -->polymorphism in input (letting a parent class accept multiple sublasses in a function (exception const&  e) )
    When to pass by value:
        -->When input is small (e.g. primitive types)
        -->When the input wouldneed to be copied anyway
*/
    
    void* z = &x;
    // Casting: converting variable from one type to another. C++ tries to automatically do it (rarely works)
    // Explicit Casting: telling compiler to convert from one type to another. Done when implicit casting doesnt apply, or gives bad type ex: (char) 42 || static_cast<char>(42)
    // Can also cast memory addresses?!?! (char*) int &y = &x; y converts whatever y is holding to a char for z. Essentially useful for casting void*
    cout << "x " << x << endl << "w " << w << endl << "y " << y << endl << "z " << z << endl ;

    // new keyword -- takes new data type and stores enough space on heap to store datatype
    // returns pointer to space allocated, remains allocated until u chhoose to free it
    // Delete takes pointer created by new and deallocates the memory, no longer safe to dereference the pointer (calling delete on pointer not allocated by new is undefined behavior)
    // Can call delete on null pointer

    int*g = new int; //Creates space for *g on heap, is uninitialized
    int*g = new int(); /*Creates space for *g on the heap, initialized to 0*/    int*g = new int(2); /*Creates space for *g on the heap, initialized to 2*/
    for(int i = 0; i < 10000; i++){
        int *p = new int(7);
        //delete p;
    } // Creates a bunch of new memory allocated for a new int, but when it goes out of scope p is uninitialized
    // When p is uninitialized, all the memory allocated for the int is unaccesible.
    // Memory leak -- when memory allocated is no longer accesible, but is still there

    int arr[] = {1, 2, 3, 4, 5};
    int arr2[5] = arr; //doesn't work. Becasue arr is a pointer, the size of arr is unknown

    int * arr2 = arr; // Arrays can be converted to pointers of appropiate type || conversion happens auto when passing array into function
    // Will assume the size of the arr2 because of arr1 || Pointers can be indexed just like arays || changing one array will change the other
    // arrays and pointers interchangable
    // Array of variable size 
    // Memory on stack is allocated by computer, memory on heap allocated by person

    int n;
    cin >> n;
    int * arr = new int[n]; //Can create variable size arrays
    delete[] arr;
    
}
