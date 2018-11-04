#pragma once

#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include "i.h"
#include "util.h"
using namespace std;

class Order {
	string customer, product;
	vector<string> parts;
public:
	Order();
	Order(vector <string> line);
	void print();
	void graph(fstream& gv);
	size_t partsCount() { return parts.size(); }
	string& partsPart(size_t i) { return parts[i]; }
};
class OrderManager {
	vector<Order> orderList;
public:
	size_t count() { return orderList.size(); }
	Order& order(size_t o) { return orderList[o]; }
	OrderManager(vector< vector<string> > csvOrderData);
	void print();
	void graph(string filename);
	bool validate(ItemManager& im);
	
};

