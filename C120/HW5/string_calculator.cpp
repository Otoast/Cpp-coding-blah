#include <iostream>
#include <string>
#include "./string_calculator.h"

using std::cout, std::endl;
using std::string;

unsigned int digit_to_decimal(char digit) {
    if(!isdigit(digit)) throw std::invalid_argument("I-I-I- BE POPPIN BOTTLES\nSPARKLES AND CHAMPANGE");
    return static_cast<int>(digit) - 48;
}

char decimal_to_digit(unsigned int decimal) {
    if (!(decimal < 10)) throw std::invalid_argument("WE LIVE\nWE LOVE\nWE LIE");
    return static_cast<char>(decimal + 48);
}

string trim_leading_zeros(string num) {
    unsigned int trimIndx = 0;
    while (num.at(trimIndx) == '0' && (trimIndx != num.length() - 1)) ++trimIndx;
    if (trimIndx >= 1) num.erase(0, trimIndx);
    return num;
}

string add(string lhs, string rhs) {
    lhs = trim_leading_zeros(lhs);
    rhs = trim_leading_zeros(rhs);
    int lhsIndex = lhs.length() - 1;
    int rhsIndex = rhs.length() - 1;
    
    int lhsNum, rhsNum, tensPlace = 0, digitSum;
    char onesPlace;
    string sumString = "";
    while(lhsIndex >= 0 || rhsIndex >= 0){
        lhsNum = (lhsIndex >= 0) ? digit_to_decimal(lhs.at(lhsIndex)) : 0;
        rhsNum = (rhsIndex >= 0) ? digit_to_decimal(rhs.at(rhsIndex)) : 0;
        digitSum = lhsNum + rhsNum + tensPlace;
        if (digitSum >= 10){
            onesPlace = decimal_to_digit(digitSum % 10);
            tensPlace = digitSum / 10;
        }
        else{
            onesPlace = decimal_to_digit(digitSum);
            tensPlace = 0;
        }
        sumString.insert(0, 1, onesPlace);
        lhsIndex -= 1;
        rhsIndex -= 1;
    }
    if (tensPlace > 0) sumString.insert(0, 1, decimal_to_digit(tensPlace));

    return sumString;




    return "";
}

string multiply(string lhs, string rhs) {
    lhs = trim_leading_zeros(lhs);
    rhs = trim_leading_zeros(rhs);
    int lhsIndex = lhs.length() - 1;
    int rhsIndex = rhs.length() - 1;
    int lhsNum, rhsNum, tensPlace = 0, digitSum, amtZerosAdd = 0;
    char onesPlace;
    string multiplyString = "";
    string sumString = "0";;
    while(rhsIndex >= 0){
    
        multiplyString.clear();
        for (int i = 0; i < amtZerosAdd; ++i) multiplyString.append("0"); 
        rhsNum = digit_to_decimal(rhs.at(rhsIndex));

        for (int i = lhsIndex; i >= 0; --i){
            lhsNum = digit_to_decimal(lhs.at(i));
            digitSum = lhsNum * rhsNum + tensPlace;
            if (digitSum >= 10){
                onesPlace = decimal_to_digit(digitSum % 10);
                tensPlace = digitSum / 10;
            }
            else{
                onesPlace = decimal_to_digit(digitSum);
                tensPlace = 0;
            }
            multiplyString.insert(0, 1, onesPlace);
        }
        if (tensPlace > 0) multiplyString.insert(0, 1, decimal_to_digit(tensPlace));
        tensPlace = 0;
        sumString = add(sumString, multiplyString);
        rhsIndex -= 1; amtZerosAdd += 1;
    }
    

    return sumString;
}
