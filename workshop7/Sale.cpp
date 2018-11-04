#include <vector>
#include <iomanip>
#include <fstream>
#include <string>
#include "Sale.h"
#include "TaxableProduct.h"
using namespace std;
namespace w7 {
	Sale::Sale(const char* fileName) {
		ifstream in(fileName, ios::in);
		if (!in.is_open()) {
			throw string("cannot open file '") + fileName + "'\n";
		} 
		else {
			string line;
			while (getline(in, line)) {
				auto cr = line.find('\r');
				if (cr != string::npos) {
					line.erase(cr, 1);
				}	
			}
			in.clear();
			in.seekg(0);
			while (in.good()) {
				products.push_back(readProduct(in));
			}
			products.pop_back();
		}
	}
	void Sale::display(ostream& os) const {
		double total = 0.0;
		os << "Product No      Cost Taxable\n";
		for (auto p : products) {
			p->display(os);
			os << "\n";
			total += p->getCharge();
		}
		os << "     Total " << setw(10) << total << "\n";

	}
	Sale::~Sale() {
		for (auto p : products)
			delete p;
	}
}