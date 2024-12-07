/******************************************************************************

    File: main.cpp
    Author: Prof. Lupoli & Andrew Nemec
    Date: 2/16/2021
    Section: 
    E-mail: slupoli@tamu.edu
    Description:
    This file contains C++  code that will simulate data collected from a track 
    event with 9 lanes. The code will sort the order, then display the results

    Updates
    Author: J. Michael Moore & Paul Taele
    Author: J. Michael Moore

    Input information format
    <Time (double)> <Abbreviated Country (String)> <Uniform number (int)> <Lastname (String)>
    32.7 USA 12 Moore
    36.5 RUS 35 Polsley
    45.8 ENG 73 Teale
    52.34 CHN 14 Nemec
    76.45 ITY 23 Lupoli     

*******************************************************************************/

#include <iostream>
#include <cstring>
#include "parallel_tracks.h"


using std::cin; using std::cout; using std::endl; using std::string;

int main()
{
    //prep all arrays
    double time[SIZE]; char country[SIZE][STRING_SIZE]; unsigned int jnumber[SIZE]; char lastname[SIZE][STRING_SIZE];
    prep_double_array(time); prep_string_array(country);  prep_unsigned_int_array(jnumber); prep_string_array(lastname);

    // load the runner's data into the array
    // if unable to load runner data
    //   1) output "Bad input" to standard out
    //   2) exit program by returning 1
    bool good_data = get_runner_data(time, country, jnumber, lastname);
    if(not good_data){
        cout << "Bad input" << endl;
        return 1;
    }

    // TODO: determine ranking, notice the rank array receives the results
    unsigned int rankArr[SIZE];
    get_ranking(time, rankArr);

    // TODO: Output results
    print_results(time, country, lastname, rankArr);

    // this is not required in C++ but many people still explitly add it
    return 0; 
}

