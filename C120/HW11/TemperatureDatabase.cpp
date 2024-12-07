# include "TemperatureDatabase.h"
# include <fstream>
#include <sstream>
using std::cout, std::endl, std::string, std::ofstream;

TemperatureDatabase::TemperatureDatabase() : records(){}
TemperatureDatabase::~TemperatureDatabase() {
}

void TemperatureDatabase::loadData(const string& filename) {
	// TODO: implement this function
	std::ifstream inFS (filename);
	if (!inFS.is_open()) {
		cout << "Error: Unable to open " << filename << endl;
		exit(1);
	}
	while (!inFS.eof()){
		string row;
		getline(inFS, row);
		if (inFS.eof()) break;
		std::istringstream inSS (row);
		
		string id, month, year, temperature;
		inSS >> id >> year >> month >> temperature;
		if (inSS.fail() || month.find_first_of('.') != string::npos || 
				year.find_last_of('.') != string::npos){
			cout << "Error: Other invalid input" << endl;
			inSS.clear();
			continue;
		}
		if (id.find_first_not_of("0123456789") != string::npos || std::stoi(id) < 0){
			cout << "Error: Invalid id " << id << endl;	
			continue;
			}
		else if (std::stoi(month) < 1 || std::stoi(month) > 12){
			cout << "Error: Invalid month " << month << endl;
			continue;
		}
		else if (std::stoi(year) < 1800 || std::stoi(year) > 2023)
		{
			cout << "Error: Invalid year " << year << endl;	
			continue;
		}
		else if (std::stof(temperature) < -50 || std::stof(temperature) > 50){
			cout << "Error: Invalid temperature " << temperature << endl;
			continue;
		}
		records.insert(id, std::stoi(year), std::stoi(month), std::stof(temperature));
		
		LinkedList newRecord = records;

	}	
}

void TemperatureDatabase::outputData(const string& filename) {
	ofstream dataout("sorted." + filename);
	
	if (!dataout.is_open()) {
		cout << "Error: Unable to open " << filename << endl;
		exit(1);
	}
	dataout << records.print();
}

// void TemperatureDatabase::performQuery(const string& filename) {
// 	// TODO: implement this function
// }
