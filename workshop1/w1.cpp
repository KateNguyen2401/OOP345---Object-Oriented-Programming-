#include <iostream>
#include "process.h"
using namespace std;
using namespace w1;

int main(int argc, char* argv[]) {
	for (int arg = 1; arg < argc; arg++)
		Process(argv[arg]);
	cout << "\n";
}