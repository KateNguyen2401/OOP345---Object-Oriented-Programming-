#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

#include "util.h"
#include "i.h"
#include "o.h"
#include "t.h"
#include "m.h"
#include "j.h"
using namespace std;
class Factory {
	vector<Machine> machineList;
public:
	Factory(ItemManager& im, OrderManager& om, TaskManager& tm) {
		//STEP 1. Create the factory
		//create a machine from each task

		for (size_t m = 0; m < tm.count(); m++) {
			machineList.emplace_back(tm.task(m));
		}
		for (auto& m : machineList)
			cout << " '" << m.getTask() << "'";
		cout << "\n"; //sanity check print

		//STEP2. Find source node
#if 1 //use for loop and find if algorithm
		for (auto& m : machineList) { //for each machine
			string pass = m.getPass();
			if (not pass.empty()) {
				//if pass exists, bump its incoming count
				auto f = [&pass](auto it) -> bool {return it.getTask() == pass; };
				find_if(machineList.begin(), machineList.end(), f)->incIncoming();
			}

			string fail = m.getFail();
			if (not fail.empty()) {
				//if fail exists, bump its incoming count
				auto f = [&fail](auto it) -> bool {return it.getTask() == fail; };
				find_if(machineList.begin(), machineList.end(), f)->incIncoming();
			}
		}
#endif

		for (auto& m : machineList) {
			//sanity check print
			cout << "'" << m.getTask() << "'";
			if (m.isSink())
				cout << " is a SINK";
			if (m.isSource())
				cout << " is a SOURCE";
			cout << "\n";
		}

		int sourceNode = -1;
		for (size_t m = 0; m < machineList.size(); m++) {
			if ( machineList[m].isSource() and machineList[m].isSink())
				continue; //ignore non-source or singleton nodes
			if (machineList[m].isSource() and sourceNode == -1) {
				//we have a source node. Is it our first source node?
				sourceNode = m;
			}
			else {
				//second sink node
				throw string("Multiple source nodes, node ") + to_string(sourceNode) + " and " + to_string(m) + " FIX TASK DATA AND RESUBMIT!!! ";
			}
		}
		cout << "sourceNode is " << sourceNode << "\n";
		if (sourceNode == -1)
			throw string("No source node FIX TASK DATA AND RESUBMIT!!! ");
		//STEP 3. Create a job from an order and add job to sourceNode machine's job queue
		for (size_t o = 0; o < om.count(); o++) {
			machineList[sourceNode].addJob(Job(om.order(o)));
		}
		for (auto& m : machineList) {
			//sanity check print
			cout << " '" << m.getTask() << "'";
			if (m.jobQSize())
				cout << " has " << m.jobQSize() << " jobs in its jobQ";
			cout << "\n";
		}

		//classify all machines as an installer or a remover
		for (auto& m : machineList) {
			m.Classify(im);
		}

		//STEP 4. Time loop
		int time = 0;
		while (true) {
			//time loop
			cout << "YOP OF TIME LOOP time=" << time << "\n";
#if 1 //use a;; of algorithm
			bool bAllDone = all_of(machineList.cbegin(), machineList.cend(), [](auto& e) {return e.jobQSize() == 0; });
#endif
			if (bAllDone) {
				cout << "ALL DONE, exiting time loop\n";
				break; //exit time loop
			}
			for (auto& m : machineList) {
				//machine loop
				//if jobQ is empty for this machine, nothing to do			
				if (m.jobQSize() == 0) {
					continue; //nothing for this machine to do
				}
				Job job = move(m.getJob());
				cout << "job " << job.customer() << "/" << job.product() << " is at machine '" << m.getTask() << "'\n";

				if (m.isSink()) {
					if (job.jobComplete()) {
						//if job complete, it is finished, all done, game over, job exists the system
						cout << "job " << job.customer() << "/" << job.product() << " terminated at machine '" << m.getTask() << "'\n";
					}
					else {
						//something needs to be installed, send it back to the source node
						cout << "job " << job.customer() << "/" << job.product() << " at machine '" << m.getTask() << "'\n";
						cout << "job not complete. re-routing back to source node"
							<< sourceNode << "(" << machineList[sourceNode].getTask() << ")"
							<< "\n";
						machineList[sourceNode].addJob(move(job));
					}
					continue; //next machine
				}

				bool bDidSomething = false;

				if (m.getInstaller()) { //are we an installer
					for (size_t i = 0; i < job.count(); i++) {
						if (job.getInstalled(i)) //ignore items already installed
							continue;
						string itemName = job.item(i); //say, 'I7'
						string installer = im.find(itemName)->getInstaller(); // say, 'INSTALL CPU'
						if (m.getTask() == installer) {
							//install the item
							job.setInstalled(i, true);
							time++;
							bDidSomething = true;
							break;
						}
					}
				}

				if(m.getRemover()){ //are we a remover?
					for (int i = job.count() - 1; i >= 0; i--) {
						//remove the last 'I7', not the first 'I7'
						if (not job.getInstalled(i)) //want to examine installed items
							continue;
						string itemName = job.item(i); //say, 'I7'
						string remover = im.find(itemName)->getRemover(); //say, 'REMOVE CPU'
						if (m.getTask() == remover) {
							//remove the item
							job.setInstalled(i, false);
							time++;
							bDidSomething = true;
							break;
						}
					}
				}

				auto moveJob = [&](string& machineName) {
#if 1 //use find_if algorithm
					auto f = [machineName](auto it) -> bool {return it.name() == machineName; };
					find_if(machineList.begin(), machineList.end(), f)->addJob(move(job));
#endif
				};
				// we know at least 'pass' and maybe 'fail' exist because wa are not a sink

				if (not bDidSomething) {
					moveJob(m.getPass()); //move 'job' to pass
					continue; // next machine in machine loop
				}

				if (m.getFail().empty()) {
					moveJob(m.getPass()); //move 'job' to pass
					continue; // next machine in machine loop
				}

				if (rand() & 1) { //say, if odd passed (1), if even failed (0)
					moveJob(m.getPass()); //move 'job' to pass
				}
				else {
					moveJob(m.getFail());
				}
				continue; // next machine in machine loop
			}
		}
		cout << "+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n";
		cout << "End of run.\n";
		cout << "The machine were active for " << time << " time units.\n";
	}
};

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


	if (im.validate(tm) and om.validate(im) and tm.validate())
		cout << "Good to go --- NO ERRORS\n";
	else
		throw string("ERRORS!");

	Factory f(im, om, tm);
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

