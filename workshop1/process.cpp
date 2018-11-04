#include <iostream>
#include "process.h"
#include "CString.h" 
using namespace std;
namespace w1 {
	void Process(char* s) {
		CString cs(s);
		cout << cs;
	}
}