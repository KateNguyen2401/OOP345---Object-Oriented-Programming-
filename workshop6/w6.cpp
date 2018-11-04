// Workshop 6 - Lambda Expression
// w6.cpp

#include <iostream>
#include <string>
#include "Grades.h"
using namespace w6;


int main(int argc, char* argv[]) {
	if (argc != 2) {
		std::cerr << argv[0] <<
			": incorrect number of arguments\n";
		std::cerr << "Usage: " << argv[0] << " file_name\n";
		return 1;
	}


	Grades grades(argv[1]);
	// define the lambda expression for letter
	auto letter = [](double grade) {
		std::string letter;
		if (grade >= 90) {
			letter = "A+";
		}
		else if (grade >= 80) {
			letter = "A";
		}
		else if (grade >= 75) {
			letter = "B+";
		}
		else if (grade >= 70) {
			letter = "B";
		}
		else if (grade >= 65) {
			letter = "C+";
		}
		else if (grade >= 60) {
			letter = "C";
		}
		else if (grade >= 55) {
			letter = "D+";
		}
		else if (grade >= 50) {
			letter = "D";
		}
		else if (grade < 50) {
			letter = "F";
		}

		return letter;
	};




	grades.displayGrades(std::cout, letter);




	std::cout << "Press any key to continue ... ";
	std::cin.get();
}