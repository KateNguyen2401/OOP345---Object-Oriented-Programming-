#ifndef W1_CSTRING_H_
#define W1_CSTRING_H_
#include <iostream>
using namespace std;
namespace w1 {
	const int MAX = 3;
	class CString {
		char s[MAX + 1];
	public:
		CString(char* ss);
		void display(ostream&);
	};
	ostream& operator<< (ostream&, CString&);
}
#endif 
