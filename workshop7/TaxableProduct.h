#pragma once
#ifndef TAXABLE_PRODUCT_H_
#define TAXABLE_PRODUCT_H_
#include "Product.h"
#define HST 1.13
#define PST 1.08
namespace w7 {
	class TaxableProduct : public Product {
	private:
		double productTax;
	public:
		TaxableProduct(int no, double cost, double tax) :Product(no, cost), productTax(tax) {}
		double getCharge() const {return Product::getCharge() * productTax;}
		void display(std::ostream& os) const;
	};
}
#endif // !TAXABLE_PRODUCT_H_
