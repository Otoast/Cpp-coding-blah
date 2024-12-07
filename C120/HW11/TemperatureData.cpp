# include "TemperatureData.h"
using std::string;

TemperatureData::TemperatureData() : id(""), year(1800), month(1), temperature(-99) {
	// TODO: implement this function
}

TemperatureData::TemperatureData(string id, int year, int month, double temperature) :
	id(id),
	year(year),
	month(month),
	temperature(temperature) {
		// Might need to verify data
	}

TemperatureData::~TemperatureData() {}

bool TemperatureData::operator<(const TemperatureData& b) {
	if (this->id < b.id) return 1;
	else if (this->id > b.id) return 0;
	
	if (this->year < b.year) return 1;
	else if (this->year > b.year) return 0;
	
	if (this->month < b.month) return 1;
	else return 0;
}

