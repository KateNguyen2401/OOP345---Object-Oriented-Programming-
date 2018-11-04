#include <string>
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;
#include "util.h"
#include "t.h"

Task::Task() {}
	Task::Task(vector <string> line) {
		cout << "Task:";
		cout << line.size() << "fields -->";
		for (auto& col : line)
			cout << " " << col;
		cout << "\n";

		switch (line.size()) {
		case 4:
			if (validtaskName(line[3]))
				fail = line[3];
			else
				throw string("Expected a s fail task name, found '") + line[3] + "'";
		case 3:
			if (validtaskName(line[2]))
				pass = line[2];
			else
				throw string("Expected a s fail task name, found '") + line[2] + "'";
		case 2:
			if (validtaskName(line[1]))
				slots = line[1];
			else
				throw string("Expected a s fail task name, found '") + line[1] + "'";
		case 1:
			if (validtaskName(line[0]))
				task = line[0];
			else
				throw string("Expected a s fail task name, found '") + line[0] + "'";
		default:
			throw string("Expected 1, 2, 3 or 4 fields, found '") + to_string(line.size());
			break;
		}
	}

	void Task::print() {
		cout << "Task/Slots/Pass/Fail = /";
		cout << task << "/";
		cout << slots << "/";
		cout << pass << "/";
		cout << fail << "/";
		cout << "\n";
	}

	void Task::graph(fstream& gv) {
		if (not pass.empty()) {
			gv << '"' << task << '"' << "->" << '"' << pass << '"' << "[color=green];\n";
		}
		if (not fail.empty()) {
			gv << '"' << task << '"' << "->" << '"' << fail << '"' << "[color=red];\n";
		}
		if (pass.empty() and fail.empty())
			gv << task << ";\n";
	}

	TaskManager::TaskManager(vector< vector<string> > csvTaskData) {
		for (auto& line : csvTaskData) {
			try {
				taskList.push_back(Task(line));
			}
			catch (string& e) {
				//for (auto& col : line)
				//	cerr << col << " ";
				cerr << "had a problem: " << e << "\n";
			}
		}
	}
	void TaskManager::print() {
		for (auto& t : taskList)
			t.print();
	}
	void TaskManager::graph(string filename) {
		fstream gv(filename.c_str(), ios::out | ios::trunc);
		if (gv.is_open()) {
			gv << "digraph task {\n";
			for (auto& t : taskList)
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
	bool TaskManager::validate() {
		int errors = 0;
		for (auto& t : taskList) {
			string pass = t.getPass();
			if (not pass.empty()) {
				if (find(pass) == nullptr) {
					errors++;
					cerr << "Task" << pass << "is unknown (not found)\n";
				}
			}
			string fail = t.getFail();
			if (not fail.empty()) {
				if (find(fail) == nullptr) {
					errors++;
					cerr << "Fail task" << fail << "is unknown (not found)\n";
				}
			}
		}
		return errors ? false : true;
 }
	Task* TaskManager::find(string name) {
		for (int i = 0; i < taskList.size(); i++) {

				if (taskList[i].getTask() == name)
					return &taskList[i];
			
		}
		return nullptr;
	}

