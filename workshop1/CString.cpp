#include <iostream>
#include "CString.h"
using namespace std;
namespace w1 {
	CString::CString(char* ss) {
		for (int i = 0; i < MAX; i++) {
			s[i] = ss[i];
			if (s[i] == '\0')
				break;
		}
		s[MAX] = '\0';
	}
	void CString::display(ostream& os) {
		os << s;
	}
	ostream& operator << (ostream& os, CString& cs) {
		static int count = 0;
		os << count << ": ";
		cs.display(os);
		os << "\n";
		count++;
		return os;
	}
}