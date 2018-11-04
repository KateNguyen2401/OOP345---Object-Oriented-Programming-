#include <string>
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;
#include "o.h"

Order::Order(){}
Order::Order(vector <string> line) {
		if (line.size() < 3) {
			throw string("Expected 3 or more fields, found '") + to_string(line.size());
		}
		customer = line[0];
		product = line[1];
		for (int i = 2; i, line.size(); i++)
			if (validItemName(line[i]))
				parts.push_back(line[i]);
			else
				throw string("expected an item name, found '") + line[i] + "'";
	}

	void Order::print() {
		cout << "customer/product/parts .../ = /";
		cout << customer << "/";
		cout << product << "/";
		for (auto & p : parts)
			cout << p << "/";
		cout << "\n";
	}

	void Order::graph(fstream& gv) {
		for (auto & p : parts)
			gv << '"' << customer
			<< "\n"
			<< '"' << product << '"' << "->" << '"' << p << '"' << "[color=blue];\n";

	}


OrderManager::OrderManager(vector< vector<string> > csvOrderData) {
		for (auto& line : csvOrderData) {
			try {
				orderList.push_back(Order(line));
			}
			catch (string& e) {
				//for (auto& col : line)
				//	cerr << col << " ";
				cerr << "had a problem: " << e << "\n";
			}
		}
	}
	void OrderManager::print() {
		for (auto& t : orderList)
			t.print();
	}
	void OrderManager::graph(string filename) {
		fstream gv(filename.c_str(), ios::out | ios::trunc);
		if (gv.is_open()) {
			gv << "digraph task {\n";
			for (auto& t : orderList)
				t.graph(gv);
			gv << "}\n";
			gv.close();

#ifdef __unix
				string dot = "dot";
#else
string dot = "C:/\"Program FIles (x86)\"/Graphviz2.38/bin/dot.exe";
#endif
string cmd = dot + " -Tpng -O " + filename;

cout << "running '" << cmd << "'\n";
system(cmd.c_str());
		}
	}
	bool OrderManager::validate(ItemManager& im) {
		int errors = 0;
		for (auto& o : orderList) {
			//check each item im the order exists
			for (size_t i = 0; i < o.partsCount(); i++) {
				string part = o.partsPart(i);
				if (im.find(part) == nullptr) {
					errors++;
					cerr << "cannot find item" << part << "\n";
				}
			}

		}
		return errors == 0;
	}



