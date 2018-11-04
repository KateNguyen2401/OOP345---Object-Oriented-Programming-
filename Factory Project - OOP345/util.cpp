#include <string>
#include <iostream>
#include <fstream>
#include <vector>

#include "util.h"

void trimSpace(std::string& s) {
	while (!s.empty() && s[0] == ' ')
		s.erase(0, 1);

	while (!s.empty() && s[s.size() - 1] == ' ')
		s.erase(s.size() - 1, 1);
}
void csvprint(std::vector<std::vector<std::string>> & csvdata) {
	//print csvdata
	for (auto& row : csvdata) {
		for (auto& column : row)
			std::cout << "(" << column << ") ";
		std::cout << "\n";
	}
}

void csvread(std::string& filename, char seperator, std::vector<std::vector<std::string>> & csvdata) {
	std::fstream in(filename.c_str(), std::ios::in);
	if (!in.is_open()) {
		throw std::string("cannot open file '") + filename + "'";
	}

	std::string line;
	while (std::getline(in, line)) {
		//look for "/r"

		auto cr = line.find('\r');
		if (cr != std::string::npos) {
			line.erase(cr, 1);
		}
		//cout << "line ->" << line << "<--\n";

		size_t index = 0;
		std::string field;
		std::vector<std::string> fields;
		while (index < line.size()) {
			if (line[index] != seperator) {
				field += line[index];
			}
			else {
				trimSpace(field);
				//field is complete
				//fields.push_back(field);			//pre c++11 method
				//field.clear();
				fields.push_back(move(field));	//simple c++11 method
												//fields.emplace_back(field);			// better c++11 method
			}
			index++;
		}
		trimSpace(field);
		fields.push_back(move(field));
		//fields.emplace_back(field);				//add field to vector, case 1 field not empty, case 2 field empty(null field)
		//print line
		//for (auto& e : fields)
		//cout << "[" << e << "] ";
		//cout << "\n";
		csvdata.push_back(move(fields));

	}

	in.close();
}


bool validtaskName(std::string s) {
	for (auto c : s) { //look for bad characters
		if (not (isalnum(c) or c == ' ' or c == '-'))
			return false;
		return true;
	}
}

bool validSlot(std::string s) {
	for (auto c : s) {
		if (not (isdigit(c))) {
			return false;
		}
		return true;
	}
}

bool validItemName(std::string s) {
	for (auto c : s) {
		if (not (isalnum(c) or c == ' ' or c == '-'))
			return false;
		return true;
	}
}

bool validSequence(std::string s) {
	for (auto c : s) {
		if (not (isdigit(c)))
			return false;
		return true;
	}
}