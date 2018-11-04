#ifndef W3_TEXT_H_
#define W3_TEXT_H_

#include <iostream>
#include <fstream>
#include <string>

namespace w3 {
	class Text {
		size_t LineCount = 0;
		std::string* LineTable = nullptr;
	public:
		Text();
		Text(char* filename);
		~Text();
		size_t size();
		Text& operator=(const Text& rhs);
		Text&& operator=(Text&& rhs);
		Text(const Text& rhs);
		Text(Text&& rhs);
	};
}
#endif
