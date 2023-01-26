#include <iostream>
#include <iomanip>
#include <string>
#include "parallel_tracks.h"
#include <fstream>
#include <sstream>

using std::string;
using std::cin;
using std::cout;
using std::ifstream;

void get_runner_data(const std::string& file, double timeArray[], std::string countryArray[], 
		unsigned int numberArray[], std::string lastnameArray[]) 
{
	ifstream inFS;
	inFS.open(file);
    while (!inFS.is_open()) {
        throw std::invalid_argument("Cannot open file");
    }

	for (unsigned int i = 0; i < SIZE; i++) {
		
		string hold = "";
		getline(inFS, hold);
		if (hold == "") {
			throw std::domain_error("File missing data");
		}

		std::stringstream ss = std::stringstream(hold);

		double input1 = 0.0;
		ss >> input1;
		if (ss.fail()) {
			throw std::domain_error("File contains invalid data (time)");
		}
		if (input1 <= 0.0) {
			throw std::domain_error("File contains invalid data (time)");
		}
		timeArray[i] = input1;

		string input2 = "";
		ss >> input2;
		if (input2.size() != 3) {
			throw std::domain_error("File contains invalid data (country)");
		}
		for (long unsigned int j = 0; j < input2.size(); j++) {
			if (!isalpha(input2.at(j))) {
				throw std::domain_error("File contains invalid data (country)");
			}
			if (!isupper(input2.at(j))) {
				throw std::domain_error("File contains invalid data (country)");
			}
		}
		countryArray[i] = input2;

		unsigned int input3 = 0;
		ss >> input3;
		if (ss.fail()) {
			throw std::domain_error("File contains invalid data (number)");
		}
		else if (input3 / 10 >= 10) {
			throw std::domain_error("File contains invalid data (number)");
		}
		numberArray[i] = input3;

		string input4 = "";
		ss >> input4;
		trim(input4);
		if (input4.size() <= 1) {
			throw std::domain_error("File contains invalid data (name)");
		}
		for (long unsigned int k = 0; k < input4.size(); k++) {
			if (!isalpha(input4.at(k))) {
				throw std::domain_error("File contains invalid data (name)");
			}
		}
		lastnameArray[i] = input4;

	}
}


void prep_double_array(double ary[])
// making sure all values within the array are set to 0.0;
{
  	for (unsigned int i = 0; i < SIZE; i++) {
		ary[i] = 0.0;
  	}
}

void prep_unsigned_int_array(unsigned int ary[])
// making sure all values within the array are set to 0;
{
	for (unsigned int i = 0; i < SIZE; i++) {
		ary[i] = 0;
	}
}

void prep_string_array(std::string ary[])
// making sure all values within the array are set to "N/A";
{
	for (unsigned int i = 0; i < SIZE; i++) {
		ary[i] = "N/A";
	}
}

void get_ranking(const double timeArray[], unsigned int rankArray[])
{
	prep_unsigned_int_array(rankArray);
	for (int k = 0; k < 9; k++) {
		double test = timeArray[k];
		int position = 1;
		for (int l = 0; l < 9; l++) {
			if (test > timeArray[l]) {
				position += 1;
			}
		}
		rankArray[k] = position;
	}
}


void print_results(const double timeArray[], const std::string countryArray[],
		const std::string lastnameArray[], const unsigned int rankArray[])
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

std::string trim(const std::string word) {
	string ret = word;

	// remove whitespace from the beginning
	while (!ret.empty() && isspace(ret.at(0))) {
			ret.erase(0, 1);
		}

	// remove whitespace from the end
	//  Note: last index is (.size() - 1) due to 0 based indexing
	while (!ret.empty() && isspace(ret.at(ret.size()-1))) {
		ret.erase(ret.size()-1, 1);
	}
	
	return ret;
}