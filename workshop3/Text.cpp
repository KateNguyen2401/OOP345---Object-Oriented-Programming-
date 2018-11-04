#include <iostream>
#include <fstream>
#include <string>
#include "Text.h"

namespace w3 {

Text::Text() {

}
Text::Text(char* filename) {
		std::fstream in(filename, std::ios::in);
		if (in.is_open()) {
			std::string line;
			while (getline(in, line))
				LineCount++;
			std::cout << "'" << filename << "' contains " << LineCount << " lines.\n";

			LineTable = new std::string[LineCount];
			in.clear(); //clear eof(end of file) error state
			in.seekp(0); //go back to the start of file
			for (size_t i = 0; i < LineCount; i++) {
				getline(in, LineTable[i]);
				if (auto cr = LineTable[i].find('/r'))
					if (cr != std::string::npos)
						LineTable[i].erase(cr, 1);
			}
				//for (size_t i = 0; i < LineCount; i++)
				//	cout << i+1 << ": '" << LineTable[i] << "'\n";
		}
		else {
			std::cerr << "Cannot open file'" << filename << "'\n";
			exit(1);
		}
}
Text::~Text() {
		delete[] LineTable;
}
size_t Text::size() {
		return LineCount;
}
Text& Text::operator=(const Text& rhs) {
		if (this != &rhs) {
			delete[] LineTable;
			LineCount = rhs.LineCount;
			LineTable = new std::string[LineCount];
			for (size_t i = 0; i < LineCount; i++)
				LineTable[i] = rhs.LineTable[i];
		}
		return *this;
}
Text&& Text::operator=(Text&& rhs) {
			//Text&& operator = (Text&& rhs)
			if (this != &rhs) {
				delete[] LineTable;
				LineCount = rhs.LineCount;
				LineTable = rhs.LineTable;
				rhs.LineCount = 0;
				rhs.LineTable = nullptr;
			}
			//return *this;
			return std::move(*this);
		}
Text::Text(const Text& rhs) {
			LineCount = rhs.LineCount;
			LineTable = new std::string[LineCount];
			for (size_t i = 0; i < LineCount; i++)
				LineTable[i] = rhs.LineTable[i];
		}
Text::Text(Text&& rhs) {
		LineCount = rhs.LineCount;	
		LineTable = rhs.LineTable;	
		rhs.LineCount = 0;
		rhs.LineTable = nullptr;
	}		
};	

