#include <iostream>

using namespace std;

/*
try/catch statements - have to be used together (enclose a block of unsafe code, if exception is thrown use catch to handle exception)
*/

int main(){

    try {
        int y = 1234567890123;
        cout << y;
        int x = std::stoi("Hello");
        cout << x + 1 << endl;
    }
    // Can write multiple catch statements
    // const& promises the compiler that you are not gonna change the exception
    catch(std::overflow_error const&){
        cout << "overflow" << endl;
    }
    catch(...) {
        cout << "Given string was not  a number."; }
    // To raise exception of out own, use throw keyword (can throw anything)
    // Undefined behavior ignores all catch statements, and C++ will do what it wants


    // Every variable in C++ has type and value (primitive, Aggregate [built from primitive types])
    // Exception is class defined in standard library
    /* EXCEPTION CLASS
            Certain classes can inheret from another class (all predefined exception classes inherit from std::exception)
            Inheritance - "is a kind of" relationship
            Can catch some errors if they are a child of a parent exception

    
    */
   try{
    // Creates an object of type "invalid argument", does not have a name
    throw std::invalid_argument("hi");
   }
   //invaid argument is a subclass of logic_error, e is the new name of the object with a permanant address
   catch(std::logic_error const& e){
    std::cout << e.what();
   }
   // if a function f throws an exception and doesn't catch it, C++ looks for a handler(catch statement) in the function that called f
   // Data validation - checking to see if input data meets requirement of function
   /*   Avoiding undefined behavior: initialize variables to default values
            Check indices against length of array before access
            Check division by 0 before performing division, check for overflow
            
   */

  // Encapsulation - idea that data should be stored in classes and accessed via those classes
  //    Groups data together & makes code easier to read. Private members improve code safety via limiting which functions can modify certain variables
  //    Defining classes alot like defining struct
}

class Runner{
    private:
    double time;
    char country[12];
    int number;
    string lastName;

    // Constructor for the class, can do so certain variables arent modified in main code
    public:
    Runner(double t, char c[], int n, string ln){
        time = t;
        country[0] = c[0];
        number = n;
        lastName = ln;

    }
    void print() {
        cout << time << country << number << lastName << endl;
    }
};

int main(){
    Runner beideman = Runner(12.20, "USA", 12, "Beideman");
    return 0;

}