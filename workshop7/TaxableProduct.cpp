#include <iomanip>
#include "Product.h"
#include "TaxableProduct.h"

namespace w7 {
	void TaxableProduct::display(std::ostream& os) const {
		Product::display(os);
		if (productTax == HST) {
			os << " HST";
		} 
		else if (productTax == PST) {
			os << " PST";
		}
	}
}