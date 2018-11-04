#ifndef STATION_H_
#define STATION_H_
#include <iostream>
#include <fstream>
#include <string>

namespace w2 {
	enum PassType {
		PassStudent, //define passStudent =0
		PassAdult,   //define passAdult =1
		PassCount     //define passType =2
	};
	class Station {
		std::string name;
		unsigned passes[PassCount];
	public:
		Station();
		Station(std::fstream& in);
		void set(const std::string& n, unsigned s, unsigned a);
		void update(PassType pt, int num);
		unsigned inStock(PassType pt) const;
		const std::string& getName() const;
		void update();
		void restock();
		void report();
	};
}
#endif