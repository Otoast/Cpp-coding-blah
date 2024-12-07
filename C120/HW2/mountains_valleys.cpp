#include <iostream>
#include "functions.h"

using std::cout, std::cin, std::endl;

int main() {
	// TODO(student): print prompt for input
	bool validRange = false;
	int firstVal, secondVal;

	while(!validRange){
		validRange = true;
		cout << "Enter numbers 10 <= a <= b < 10000: ";

		cin >> firstVal >> secondVal;
		validRange = is_valid_range(firstVal, secondVal);
		if(!validRange) {cout << "Invalid Input" << endl;}
	}

	count_valid_mv_numbers(firstVal, secondVal);



	// TODO(student): validate input (and reprompt on invalid input)

	// TODO(student): compute and display solution
	
	return 0;
}