#pragma once
#ifndef SALE_H_
#define SALE_H_
#include <vector>

#include "Product.h"
namespace w7 {
	class Sale {
	private:
		std::vector <iProduct*> products;
	public:
		Sale(const char* fileName);
		void display(std::ostream& os) const;
		~Sale();
	};
}
#endif // !SALE_H_