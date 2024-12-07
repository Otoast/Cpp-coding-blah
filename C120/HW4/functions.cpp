#include <iostream>
#include <stdexcept>
#include "functions.h"
int Largest(int a, int b, int c) {
  int d = a;
  if (a > d) {
    d = a;
  } if (b > d) {
    d = b;
  } if (c > d) {
    d = c;
  }
  return d;
}

bool SumIsEven(int a, int b) {
  if((a + b) % 2)
    return false;
  else
    return true;
  // For default
  return false; 
}


int BoxesNeeded(int apples) {
  if (apples < 0) return 0;
  int boxesNeeded = apples / 20;
  if (apples % 20 > 0) boxesNeeded += 1;
  return boxesNeeded;
}

bool SmarterSection(int A_correct, int A_total, int B_correct, int B_total) {

  if (A_correct < 0 || A_total < 0 || B_correct < 0 || B_total < 0){
    throw std::invalid_argument("Invalid arguments");
  }
  double A_percentage = static_cast<double>(A_correct) / A_total;
  double B_percentage = static_cast<double>(B_correct) / B_total;
  if (A_percentage > 1 || B_percentage > 1) throw std::invalid_argument("Invalid arguments");
  return A_percentage > B_percentage;

}

bool GoodDinner(int pizzas, bool is_weekend) {
  if (!is_weekend){
    if (pizzas >= 10 && pizzas <= 20) return true;
    else return false;
  }
  if (is_weekend) {
    if (pizzas >= 10) return true;
    else return false;
  }
  // default
  return false;
}

int SumBetween(int low, int high) {
  if (low > high) throw std::invalid_argument("Invalid arguments");
  int lowBound = low;
  int highBound = high;
  // test case: -1, 4
  if (high > 0 && low < 0){
    // tempVal holds how much greater high is than the absolute value of low
    int tempVal = high + low;
    // Should only add the numbers that cant be cancelled
    //  ex: sumBetween(-2, 4) should only add 3, 4
    if (tempVal > 0)
      { 
      lowBound = high - (tempVal - 1); 
      highBound = high; }
    //  ex: sumBetween(-4, 2) should only add -4, -3
    else if (tempVal < 0) 
      {
        lowBound = low; 
        highBound = low - (tempVal + 1); }
    // Only returns if abs value of low = high
    else return 0;
  }

  if (low == high) return low;
  int value = 0;
  for (int n = lowBound; n < highBound + 1; n++) {
    // Check it wont overflow before adding
    if ((n < 0) && value < INT32_MIN - n)
      { throw std::overflow_error("Sum exceeds maximum/minimum value of int"); }
    else if ((n > 0) && value > INT32_MAX - n)
      { throw std::overflow_error("Sum exceeds maximum/minimum value of int:");}
    value += n;
  }
  return value;
}

int Product(int a, int b) {
  // Four test cases (++, +- , -+, --)
 if (a > 0){
  if (b > INT32_MAX / a || b < INT32_MIN / a)
    { throw std::overflow_error("The product of these two values will cause overflow"); }
 }
 else if (a < 0){
  if (b < INT32_MAX / a || b > INT32_MIN / a)
    { throw std::overflow_error("The product of these two values will cause overflow"); }
 }
 else return 0;
  return a * b;
}