#pragma once
#ifndef PRODUCT_H_
#define PRODUCT_H_

#include "iProduct.h"
namespace w7 {
	class Product : public iProduct {
	private:
		int productNo;
		double productCost;
	public:
		Product(int no, double cost) : productNo(no), productCost(cost) {}
		double getCharge() const { return productCost; }
		void display(std::ostream& os)const;
	};
}
#endif 