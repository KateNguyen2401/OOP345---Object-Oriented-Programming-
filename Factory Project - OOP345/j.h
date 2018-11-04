#pragma once
#include "o.h"

class Job : public Order {
	std::vector<bool> installed;
public:
	bool getInstalled(size_t i) const { return installed[i]; }
	void setInstalled(size_t i, bool v) { installed[i] = v; }

	bool jobComplete() const {
#if 1 // use std::all of algorithm
		return std::all_of(installed.cbegin(), installed.cend(), [](bool e) {return e == true; });
#endif
	}

	Job():Order() {

	}
	
	Job(Order& o) :Order(o) {
		for (size_t i = 0; i < count(); i++)
			installed.push_back(false);
	}

};