#include <iomanip>
#include "Product.h"
#include "TaxableProduct.h"

using namespace std;
namespace w7 {
	iProduct* readProduct(ifstream& fs) {
		int tempNo;
		double tempCost;
		char tempTax;
		iProduct *product = nullptr;
		fs >> tempNo >> tempCost;
		if (fs.get() != '\n') {
			fs.get(tempTax);
			if (tempTax == 'H') {
				TaxableProduct* tempProduct = new TaxableProduct(tempNo, tempCost, HST);
				product = tempProduct;
			}
			else if (tempTax == 'P'){
				TaxableProduct* tempProduct = new TaxableProduct(tempNo, tempCost, PST);
				product = tempProduct;
			}
		}
		else {
			Product* tempProduct = new Product(tempNo, tempCost);
			product = tempProduct;
		}
		return product;
	}
	ostream& operator<< (ostream& os, const iProduct* p) {
		p->display(os);
		return os;
	}
	void Product::display(ostream& os) const {
		os << setw(10) << productNo << right << setw(10) << std::fixed << std::setprecision(2) << Product::getCharge();
	}
}