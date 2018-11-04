#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include "util.h"
#include "t.h"
using namespace std;

class Item {
	std::string item, installer, remover, sequence, description;
public:
	Item();
	Item(std::vector <std::string> line);
	string& getItem() { return item; };
	string& getInstaller() { return installer; };
	string& getRemover() { return remover; };
	void print();
	void graph(std::fstream& gv);
};

class ItemManager {
	vector<Item> itemList;
public:
	size_t count() { return itemList.size(); }
	Item& item(size_t i) { return itemList[i]; }
	ItemManager(vector< vector<string> > csvTaskData); 
	void print();
	void graph(string filename);
	bool validate(TaskManager& tm);
	Item* find(string item);

};
