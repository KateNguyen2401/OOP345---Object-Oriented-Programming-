#ifndef STATIONS_H_
#define STATIONS_H_

#include <iostream>
#include <fstream>
#include <string>
#include "Station.h"

namespace w2 {
	class Stations {
		int stationsCount = 0; //C++4 initilization
		Station* stationTable = nullptr;
	public:
		Stations(const char* filename);
		~Stations();
		void update() const;
		void restock() const;
		void report() const;
	};
}
#endif
