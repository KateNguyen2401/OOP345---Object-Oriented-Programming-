#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <cstdlib>
 
#include "Stations.h"
#include "Station.h"

namespace w2 {
	Station::Station() {
		
	}
	Station::Station(std::fstream& in) {
		int passAdult = 0;
		int passStudent = 0;
		std::string pname;
		std::string line;
		int index = 0;
		std::getline(in, line);
		while (index < line.size() && line[index] != ';') {
			pname += line[index];
			index++;
		}
		if (index < line.size() && line[index] != ';') {
			std::cerr << "ERROR: Unknown data file type\n";
			std::cerr << "- missing semicolon following station name.\n";
			exit(3);
		}
		index++; //skip ';'
		while (index < line.size() && isdigit(line[index])) {
			passStudent = 10 * passStudent + (line[index] - '0');
			index++;
		}
		if (index < line.size() && line[index] != ' ') {
			std::cerr << "ERROR: Unknown data file type\n";
			std::cerr << "- missing space ' ' following student count.\n";
			exit(4);
		}
		index++;
		while (index < line.size() && isdigit(line[index])) {
			passAdult = 10 * passAdult + (line[index] - '0');
			index++;
		}
		if (index != line.size()) {
			std::cerr << "ERROR: Unknown data file type\n";
			std::cerr << "- extra characters after adult count.\n";
			exit(5);
		}
		set(pname, passStudent, passAdult);
	}
	void Station::set(const std::string& n, unsigned s, unsigned a) {
		name = n;
		passes[PassStudent] = s;
		passes[PassAdult] = a;
	} // sets the instance variables to the values received in its parameters
	
	void Station::update(PassType pt, int num) {
		passes[pt] += num;
	}// updates the number of passes - sold if negative, added if positive
	unsigned Station::inStock(PassType pt) const {
		return passes[pt];
	}// returns the number of passes of the requested type
	const std::string& Station::getName() const {
		return name;
	} //returns a reference to a string object holding the name of the station
	void Station::update() {
		std::cout << getName() << "\n";
		int s, a;
		std::cout << " Student Passes sold : "; 
		std::cin >> s;
		std::cout << " Adult   Passes sold : ";
		std::cin >> a;
		update(PassStudent, -s);
		update(PassAdult, -a);
	}

	void Station::restock(){
		std::cout << getName() << "\n";
		int s, a;
		std::cout << " Student Passes added : ";
		std::cin >> s;
		std::cout << " Adult   Passes added : ";
		std::cin >> a;
		update(PassStudent, +s);
		update(PassAdult, +a);
	}

	void Station::report() {
		std::cout << std::left << std::setw(22) << getName();
		std::cout << std::right << std::setw(3) << inStock(PassStudent);
		std::cout << std::right << std::setw(6) << inStock(PassAdult) << "\n";
	}
};

