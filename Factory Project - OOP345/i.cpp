#pragma once

#include <string>
#include <iostream>
#include <fstream>
#include <vector>

#include "util.h"
#include "i.h"
using namespace std;

Item::Item(){}
Item::Item(vector <string> line) {
	/*cout << "Task:";
		cout << line.size() << "fields -->";
		for (auto& col : line)
		cout << " " << col;
		cout << "\n";
		*/
		switch (line.size()) {
		case 5: //fail
			description = line[4];
		case 4://sequence
			if (validSequence(line[3]))
				sequence = line[3];
			else
				throw string("Expected a sequence name, found '") + line[3] + "'";
		
			if (validtaskName(line[2]))
				remover = line[2];
			else
				throw string("Expected a remover task, found '") + line[2] + "'";
		
			if (validtaskName(line[1]))
				installer = line[1];
			else
				throw string("Expected a installer task, found '") + line[1] + "'";
		
			if (validItemName(line[0]))
				item = line[0];
			else
				throw string("Expected a item name, found '") + line[0] + "'";
			break;
		default:
			throw string("Expected 4 or 5 fields, found '") + to_string(line.size());
			break;
		}
	}

	void Item::print() {
		cout << "item/installer/remover/sequence/description = /";
		cout << item << "/";
		cout << installer << "/";
		cout << remover << "/";
		cout << sequence << "/";
		cout << description << "/";
		cout << "\n";
	}

	void Item::graph(fstream& gv) {
		gv << '"' << item << '"' << "->" << '"' << installer << '"' << "[color=green];\n";
		gv << '"' << item << '"' << "->" << '"' << remover << '"' << "[color=red];\n";

	}

	ItemManager::ItemManager(vector< vector<string> > csvTaskData) {
		for (auto& line : csvTaskData) {
			try {
				itemList.push_back(Item(line));
			}
			catch (string& e) {
				//for (auto& col : line)
				//	cerr << col << " ";
				cerr << "had a problem: " << e << "\n";
			}
		}
	}
	void ItemManager::print() {
		for (auto& t : itemList)
			t.print();
	}
	void ItemManager::graph(string filename) {
		fstream gv(filename.c_str(), ios::out | ios::trunc);
		if (gv.is_open()) {
			gv << "digraph task {\n";
			for (auto& t : itemList)
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
	bool ItemManager::validate(TaskManager& tm) {
		int errors = 0;
		for (size_t i = 0; i < itemList.size(); i++) {
			string installer = itemList[i].getInstaller;
			if (tm.find(installer) == nullptr) {
				errors++;
				cerr << "Installer task " << installer << " missing (not found)\n";
			}
			string remover = itemList[i].getRemover();
			if (tm.find(remover) == nullptr) {
				errors++;
				cerr << "Remover task " << remover << " missing (not found)\n";
			}
		}
		return errors? false:true;
	}
	Item* ItemManager::find(string item){
		for (size_t i = 0; i < itemList.size(); i++) {
			if (itemList[i].getItem() == item)
				return &itemList[i];
		}
		return nullptr;
	}


	