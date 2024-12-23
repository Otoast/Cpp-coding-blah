#include <iostream>
#include <cmath>
#include "./nth_root.h"
using namespace std;
int main() {
    {   // MINIMUM REQUIREMENT (for this lab)
        // just call the function with various values of n and x
        for(int n = -7; n < 6; ++n){
            for(double x = -7; x < 6; ++x){
                nth_root(n, n/x);
                nth_root(n, n*n/x);
                nth_root(n, x);
                nth_root(n, x*x/n);
            }
            nth_root(1999, -1999); nth_root(-1999, 1999); nth_root(1999, 1999); nth_root(-1999, -1999);
            nth_root(1999, -1/2); nth_root(1999, 1/2); nth_root(-1999, 1/2); nth_root(-1999, -1/2);
        }
   
        

        

    }

    {   // TRY HARD
        // report the value
        double actual = nth_root(2, 1);
        std::cout << "nth_root(2, 1) = " << actual << std::endl;
    }

    {   // TRY HARDER
        // compare the actual value to the expected value
        double actual = nth_root(2, 1);
        double expected = 1;
        if (std::fabs(actual - expected) > 0.00005) {
            std::cout << "[FAIL] (n=2, x=1)" << std::endl;
            std::cout << "  expected nth_root(2, 1) to be " << expected << std::endl;
            std::cout << "  got " << actual << std::endl;
        } else {
            std::cout << "[PASS] (n=2, x=1)" << std::endl;
        }
    }
}
