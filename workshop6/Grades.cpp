#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "Grades.h"

namespace w6 {
	Grades::Grades(){

	}
	Grades::Grades(const char* filename) {
		std::fstream in(filename, std::ios::in);
		if (!in.is_open()) {
			throw std::string("cannot open file '") + filename + "'";
		}
		std::string line;
		while (std::getline(in, line)) { //find '\r'
			auto cr = line.find('\r');
			if (cr != std::string::npos) {
				line.erase(cr, 1);
			}
			count++;
		}
		in.clear(); //clear eof(end of file) error state
		in.seekg(0);//go back to the start of file
		int i = 0;
		while (i< count) {
			int tempNo = 0;
			double tempGrade = 0.0;
			in >> tempNo;
			in >> tempGrade;
			studentNo.push_back(tempNo);
			studentGrade.push_back(tempGrade);
			i++;
		}
		in.close();
	}
	void Grades::displayGrades(std::ostream& os, std::string(*grade) (double grade))const {
		for (size_t i = 0; i < studentNo.size(); i++) {
			os << studentNo[i] << " " << studentGrade[i] << " " << grade(studentGrade[i]) << "\n";
		}
	}
	Grades::~Grades() {

	}
}