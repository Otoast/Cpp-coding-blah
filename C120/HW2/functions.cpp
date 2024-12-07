#include <iostream>
#include "functions.h"

using std::cout, std::endl;


bool is_valid_range(int a, int b) {
	bool range_checker = (a <= b && (a >= 10 && b >= 10 && a < 10000 && b < 10000));
	return range_checker;
}

char classify_mv_range_type(int number) {

	int tempNum = number, NUM_SIZE;
	for (NUM_SIZE = 0; tempNum != 0; ++NUM_SIZE) {tempNum = tempNum / 10;}
	

int maxSplice = 1;
for(int i = 0; i < NUM_SIZE; ++i) {maxSplice *= 10;}

// Mountain check
bool isMountain = true;
for(int i = 0; i < NUM_SIZE - 1; ++i){

	int decreaseSplice = 10;
	for(int j = 0; j < i; ++j) {decreaseSplice *= 10;}
	
	int tempDigit1 = number / (maxSplice / decreaseSplice) % 10;
	int tempDigit2 = number / (maxSplice / (decreaseSplice * 10)) % 10;
	if(!((tempDigit1 < tempDigit2) && (i % 2 == 0))) {
		if (!((tempDigit1 > tempDigit2) && (i % 2 == 1))) {
		isMountain = false;
		break;
	}
}

}
if (isMountain) {return 'M';};

// Valley Check
bool isValley = true;
for(int i = 0; i < NUM_SIZE - 1; ++i){

	int decreaseSplice = 10;
	for(int j = 0; j < i; ++j) {decreaseSplice *= 10;}
	
	int tempDigit1 = number / (maxSplice / decreaseSplice) % 10;
	int tempDigit2 = number / (maxSplice / (decreaseSplice * 10)) % 10;
	if(!((tempDigit1 > tempDigit2) && (i % 2 == 0))) {
		if (!((tempDigit1 < tempDigit2) && (i % 2 == 1))) {
		isValley = false;
		break;
	}
}

}
if (isValley) {return 'V';};

return 'N';




}



void count_valid_mv_numbers(int a, int b) {
	int valleyCount = 0;
	int mountainCount = 0;
	int neitherCount = 0;
	for (int i = 0; i < (b - a) + 1; ++i){
		switch (classify_mv_range_type(a + i)) {
			case 'M':
				mountainCount += 1;
				break;
			case 'V':
				valleyCount += 1;
				break;
			default:

				neitherCount += 1;
		}
	}
	cout << "There are " << mountainCount << " mountain ranges and " << valleyCount << " valley ranges \
between " << a << " and " << b << "." << endl;
}


