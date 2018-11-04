#pragma once
#include <queue>
#include "t.h"
#include "j.h"

class Machine : public Task {
	int incoming = 0; //number of incoming edges to this node
	std::queue<Job> jobQ;
	bool bInstaller = false;
	bool bRemover = false;
public:
	void incIncoming() { incoming++; };
	bool isSink() { return getPass().empty() and getFail().empty(); } //NOTE: if pass is empty, fail must be empty.
	bool isSource() const { return incoming == 0; }

	void addJob(Job&& j) { jobQ.push(std::move(j)); }
	Job getJob() { Job job = std::move(jobQ.front()); jobQ.pop(); return job; }
	size_t jobQSize() const { return jobQ.size(); }

	bool getInstaller() const { return bInstaller; }
	bool getRemover() const { return bRemover; }
	void Classify(ItemManager& im) {
		for (size_t i = 0; i < im.count(); i++) {
			if (getTask() == im.item(i).getInstaller())
				bInstaller = true;
			if (getTask() == im.item(i).getRemover())
				bRemover = true;
		}

		if (bInstaller && bRemover)
			throw getTask() + " is both an installer and a remover. Fix item data and re-submit!";
	}
	
	Machine() :Task() {

	}
	Machine(Task& t) :Task(t) {

	}
};
