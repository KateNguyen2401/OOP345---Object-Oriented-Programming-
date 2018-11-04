#include <string>
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;
#include "util.h"
#include "i.h"
#include "o.h"
#include "t.h"

int app(int argc, char* argv[]) {
	if (argc != 5) {
		throw string("usage: ") + argv[0] + "item.dat order.dat task.dat seperator-character\n";
	}
	string filenameItem = argv[1];
	string filenameOrder = argv[2];
	string filenameTask = argv[3];
	char seperator = argv[4][0];

	vector< vector<string> > csvdataItem;
	vector< vector<string> > csvdataOrder;
	vector< vector<string> > csvdataTask;
	
	csvread(filenameItem, seperator, csvdataItem);
	csvread(filenameOrder, seperator, csvdataOrder);
	csvread(filenameTask, seperator, csvdataTask);

	csvprint(csvdataItem);
	csvprint(csvdataOrder);
	csvprint(csvdataTask);

	ItemManager im(csvdataItem);
	im.print();
	im.graph(filenameItem + ".gv");

	OrderManager om(csvdataOrder);
	om.print();
	om.graph(filenameOrder + ".gv");

	TaskManager tm(csvdataTask);
	tm.print();
	tm.graph(filenameTask + ".gv");

	
	if (im.validate(tm) and om.validate(im) and tm.validate() )
		cout << "Good to go --- NO ERRORS\n";
	else
		cout << "ERRORS! \n";
}
int main(int argc, char* argv[]) {
	int result = 0;
	try {
		result = app(argc, argv);
	}
	catch (const string& e) {
		cerr << e << "\n";
		result = 1;
	}
	return result;
}

