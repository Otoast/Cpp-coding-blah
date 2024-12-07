#include <iostream>
#include <string>
#include <limits>
#include "./string_calculator.h"
#include <sstream>
using std::cout, std::endl, std::cin;
using std::string; using std::istringstream;

int main() {
    cout << "String Calculator" << endl;
    cout << "\"q\" or \"quit\" or ctrl+d to exit" << endl;
    // TODO(student): implement the UI
    string totalString = "", solution = "", number1 = "", number2 = "";
    char operand; 
    istringstream calcISS;


   while (!cin.fail() && !calcISS.fail()){
        calcISS.clear();
        solution.clear();
        cout << ">>"; cout.flush();

        getline(cin, totalString);
        cout << endl;
        calcISS.str(totalString);
        calcISS  >> number1;
        if ((number1 == "q" || number1 == "quit")) break;
        calcISS >> std::skipws >> operand;
        calcISS >> std::skipws >> number2;
        if ((number2 == "q" || number2 == "quit")) break;

        switch (operand){
            case '+':
                solution = add(number1, number2);
                break;
            case '*':
                solution = multiply(number1, number2);
                break;
            default:
                cout << "Please only use addtion or multiplacion signs." << endl;
                break;
        }
        
        cout << "ans =\n" << endl;
        cout << "    " << solution << endl;
        cout << endl;

    }
    cout << "farvel!"; cout.flush();
    
}

