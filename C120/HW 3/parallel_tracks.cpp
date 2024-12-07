#include <iostream>
#include <iomanip>
#include <cstring>
#include "parallel_tracks.h"

using std::cin, std::cout, std::endl;

//-------------------------------------------------------
// Name: prep_double_array
// PreCondition:  an array of doubles is passed in
// PostCondition: data in the array is 'zeroed' out
//---------------------------------------------------------
void prep_double_array(double ary[])
// making sure all values within the array are set to 0.0;
{
  for(unsigned int i = 0; i < SIZE; ++i) {ary[i] = 0.0;}
}

//-------------------------------------------------------
// Name: prep_unsigned_int_array
// PreCondition:  an array of unsigned ints is passed in
// PostCondition: data in the array is 'zeroed' out
//---------------------------------------------------------
void prep_unsigned_int_array(unsigned int ary[])
// making sure all values within the array are set to 0;
{
for(unsigned int i = 0; i < SIZE; ++i) {ary[i] = 0;}
}

//-------------------------------------------------------
// Name: prep_string_array
// PreCondition:  an array of strings is passed in
// PostCondition: each element in the array is set to "N/A"
//---------------------------------------------------------
void prep_string_array(char ary[][STRING_SIZE])
// making sure all values within the array are set to "N/A";
{
	for(unsigned int i = 0; i < SIZE; ++i){
		ary[i][0] = 'N'; ary[i][1] = '/'; ary[i][2] = 'A'; ary[i][3] = '\0';
	}
}

//-------------------------------------------------------
// Name: trim
// PreCondition:  the cstring
// PostCondition: whitespace has been removed from beginning and end of string
//---------------------------------------------------------
void trim(char str[STRING_SIZE]) {
	int indx = 0;
	int indxT = 0;
	char temp[STRING_SIZE];
	// First part moves to first instance of text
	while(std::isspace(str[indx])){indx += 1;}

	// Second part adds to temp array if they are chars or if the next value after it will be a char
	while(str[indx] != '\0'){
		if (std::isspace(str[indx]) && (std::isspace(str[indx + 1]) || str[indx + 1]== '\0'))
			{	
				break;
			}
		temp[indxT] = str[indx];
		indx += 1; indxT += 1;
	}
	// Adds a null temrinator at the end
	temp[indxT] = '\0';
	std::strcpy(str, temp);
}

//-------------------------------------------------------
// Name: get_runner_data
// PreCondition:  the prepped parallel arrays
// PostCondition: all arrays contain data from standard in
//---------------------------------------------------------
bool get_runner_data(double timeArray[], char countryArray[][STRING_SIZE], 
		unsigned int numberArray[], char lastnameArray[][STRING_SIZE]) {
	
	// The line that cin will store text read from, text_holder will be used to handle different sections of the line
	char line[STRING_SIZE];
	char text_holder[STRING_SIZE];

	// Loops through all 9 lines of the text file
	for(unsigned int RUNNER_DATA_INDEX = 0; RUNNER_DATA_INDEX < SIZE; RUNNER_DATA_INDEX += 1){
		//index for line, times happen for how many times data was collected from line, index for the textholder
		int INDEX = 0; int times_happened = 0; int TEXT_HOLDER_INDEX = 0;
		cin.getline(line, 51); 
	
		// If the end of the line hasnt been reached or collecting data has happned less than 4 times, code will run
		while (line[INDEX] != '\0' || times_happened < 4)
		{
			// While the line hasnt reached a whitespace it will copy text into text_holder. When it reaches a whitespace the else statement will execute
			if (line[INDEX] != ' ' && line[INDEX] != '\0'){
				text_holder[TEXT_HOLDER_INDEX] = line[INDEX];
				INDEX += 1; TEXT_HOLDER_INDEX += 1;
				}
	
			// Code runs when name string is approached
			else{
				if(times_happened == 3){
					while (line[INDEX] != '\0'){
					text_holder[TEXT_HOLDER_INDEX] = line[INDEX];
					INDEX += 1; TEXT_HOLDER_INDEX += 1;}

			// Will reset the text_holder index but NOT the line index,  move line index to next data, and based on how many times its repeated this operation, the data will be put
			// in its correct array.
				}
				else while(line[INDEX] == ' ' && line[INDEX] != '\0') {INDEX += 1;}
				text_holder[TEXT_HOLDER_INDEX] = '\0';
				TEXT_HOLDER_INDEX = 0;
				times_happened += 1;
		

				// Differs based on how many times its put data into a parallel array
				switch (times_happened){
					case 0: default:
						return false;
						break;
					case 1:
						timeArray[RUNNER_DATA_INDEX] = std::atof(text_holder);
						if(timeArray[RUNNER_DATA_INDEX] < 0.0) {return false;}
						break;
					case 2:
						if (std::strlen(text_holder) != 3) return false;
						for(int i = 0; text_holder[i] != '\0'; ++i){
							if (!std::isalpha(text_holder[i]) || !std::isupper(text_holder[i]))
								{return false;}
							}
						std::strcpy(countryArray[RUNNER_DATA_INDEX], text_holder);
						break;
					case 3:
						numberArray[RUNNER_DATA_INDEX] = std::atoi(text_holder);
						if(numberArray[RUNNER_DATA_INDEX] > 100){return false;}
						break;
					case 4:
						trim(text_holder);
						if (std::strlen(text_holder) <= 1) return false;
						for(int i = 0; text_holder[i] != '\0'; ++i){
							if (!std::isalpha(text_holder[i]) && !std::isspace(text_holder[i])) return false;}
						std::strcpy(lastnameArray[RUNNER_DATA_INDEX], text_holder);
						break;
				}



			}


		}
	}

  return true; // set so it will compile
}

//-------------------------------------------------------
// Name: get_ranking
// PreCondition:  just the time array is passed in, and has valid data
// PostCondition: after a very inefficient nested loop to determine the placements 
// and places the ranks in a new array. That new array is returned
//---------------------------------------------------------
void get_ranking(const double timeArray[], unsigned int rankArray[])
{
	// Adds 1 to ranking for every person that beats the particular person's time
	for (unsigned int timeIndx = 0; timeIndx < SIZE; ++timeIndx){
		int rank = 1;
		double temp_value = timeArray[timeIndx];
		for (unsigned int compIndx = 0; compIndx < SIZE; ++compIndx){
			if(temp_value > timeArray[compIndx]){rank += 1;}
		}
		rankArray[timeIndx] = rank;
	}


	}



//-------------------------------------------------------
// Name: print_results
// PreCondition:  all parallel arrays are passed in and have valid data
// PostCondition: after a very inefficient nested loop to determine the ranks
// it then displays them along with a delta in time from the start
//---------------------------------------------------------
void print_results(const double timeArray[], const char countryArray[][STRING_SIZE],
		const char lastnameArray[][STRING_SIZE], const unsigned int rankArray[])
{

	std::cout << "Final results!!";
	std::cout << std::setprecision(2) << std::showpoint << std::fixed << std::endl;
	double best_time = 0.0;
		
	// print the results, based on rank, but measure the time difference_type
	for(unsigned int j = 1; j <= SIZE; j++)
	{
		
		// go thru each array, find who places in "i" spot
		for(unsigned int i = 0; i < SIZE; i++)
		{
			if(rankArray[i] == 1) // has to be a better way, but need the starting time
			{
				best_time = timeArray[i];
			}
			
			
			if(rankArray[i] == j) // then display this person's data
			{
				// this needs precision display
				std::cout << "[" << j << "]  " << timeArray[i] << " " << std::setw(15) << std::left << lastnameArray[i] << "\t" << "(" << countryArray[i] << ")  +" << (timeArray[i] - best_time) << std::endl; 
			}
			
		}
	}	
}