#include <string>
#pragma once

#include <iostream>
#include <fstream>
#include <vector>
using namespace std;
#include "util.h"

class Task {
	string task, slots = "1", pass, fail;
public:
	Task();
	Task(vector <string> line);
	string& getPass() { return pass; }
	string& getTask() { return task; }
	string& getFail() { return fail; }
	void print();
	void graph(fstream& gv);
};
class TaskManager {
	vector<Task> taskList;
public:
	size_t count() { return taskList.size(); }
	Task& task(size_t t) { return taskList[t]; }
	//TaskManager();
	TaskManager(vector< vector<string> > csvTaskData);
	void print();
	void graph(string filename);
	bool validate();
	Task* find(string name);
};

