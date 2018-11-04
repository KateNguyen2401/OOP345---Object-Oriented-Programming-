#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>

#include "Station.h"
#include "Stations.h"

namespace w2 {
		Stations::Stations(const char* filename) {
			std::fstream in(filename, std::ios::in);
			if (in.is_open()) {
				std::string line;
				int index = 0;
				std::getline(in, line);
				while (index < line.size() && isdigit(line[index])) {
					stationsCount = 10 * stationsCount + (line[index] - '0');
					index++;
				}
				if (line[index] != ';') {
					std::cerr << "ERROR: Unknown data file type\n";
					std::cerr << "- character following station count must be a semicolon. We found -->" << line[index] << "<--\n";
					exit(2);
				}
				index++;
				if (index != line.size()) {
					std::cerr << "ERROR: Unknown data file type\n";
					std::cerr << "- extra characters following station count ';' \n";
					exit(3);
				}
				stationTable = new Station[stationsCount];
				for (int i = 0; i < stationsCount; i++)
					stationTable[i] = Station(in);

			}
			else {
				std::cerr << "cannot open file '" << filename << "\n";
				exit(2);
			}

		}
		Stations::~Stations() {
			if (stationTable) {
				delete[] stationTable;			}
		}
		void Stations::update() const{
			std::cout << "\nPasses sold :\n";
			std::cout << "-------------\n";
			for (int s = 0; s < stationsCount; s++) {
				stationTable[s].Station::update();
			}
		}
		void Stations::restock() const{
			std::cout << "\nPasses Added :\n";
			std::cout << "--------------\n";
			for (int s = 0; s < stationsCount; s++)
				stationTable[s].Station::restock();
		}
		void Stations::report() const{
			std::cout << "\nPasses in Stock : Student Adult\n";
			std::cout << "-------------------------------\n";
			for (int s = 0; s < stationsCount; s++)
				stationTable[s].Station::report();
		}
	};
