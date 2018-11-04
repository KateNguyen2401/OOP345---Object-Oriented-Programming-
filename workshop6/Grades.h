#pragma once
#ifndef _GRADES_H_
#define _GRADES_H_
#include <vector>
#include <fstream>
#include <string>

namespace w6 {
	class Grades {
	private:
		std::vector<int> studentNo;
		std::vector<double> studentGrade;
		int count = 0;

	public:
		Grades();
		Grades(const char* filename);
		~Grades();
		void displayGrades(std::ostream& os, std::string(*grade)(double grade)) const;

	};
}


#endif

