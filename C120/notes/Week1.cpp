

#include <iostream>

/*
int main() {
     double num1, num2, num3;
     std::cout<<"Enter the first number!" <<std::endl;
    // cin is essentially the input for C++. Instead of parenthesis you'll use >>

    // cout is the output to console for C++. Instead of parenthesis, the output should be put in between <<  >>. use endl to move console printing to next line
    std::cin >> num1;
    std::cout<<"Enter the second number!" <<std::endl;
    std::cin >> num2;
    std::cout<<"Enter the third number!" <<std::endl;
    std::cin >> num3;
    double totalSum = num1 + num2 + num3;
    std::cout<< totalSum/3 <<std::endl;

    // because the method returns an int, put return 0 at the end. Not extremely important
    return 0;
}

*/

//------------------------------------------------------------------------------------8_25--------------------------------------------------------------------------------------------

int add(int x, int y);

int main(){
    std::cout<<"Give two values to add: ";
    int x, y;
    std::cin >> x;
    std::cin >> y;
    std::cout << add(x, y) << std::endl;


    return 0;
}

// Can have two functions of the samae name, as long as they provide different return types
    // You can also put these methods in a different file, and as long as you delcare them before you run your code it should work properly.
    // EX: int add(int x, int y) and the methods are in a different file in the same folder. 
    // Alternatively, you can use #include "filename.type" to avoid those previous declarations.
int add(int x, int y) {

    return x + y;
}

double add(double x, double y){
    return x + y;
}