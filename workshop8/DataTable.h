#pragma once
#ifndef _DATATABLE_H_
#define _DATATABLE_H_

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <numeric>
#include <iomanip>
#include <sstream>

using namespace std;
namespace w8 {
	template<typename T>
	class DataTable {
		int width;
		int noOfDec;
		vector<T> x;
		vector<T> y;
	public:
		DataTable(ifstream& is, int fwidth, int no) : width(fwidth), noOfDec(no) {
			T tx, ty;
			while (is.good()) {
				std::string line;
				while(getline(is, line)){
					auto cr = line.find('\r');
					if (cr != std::string::npos)
						line.erase(cr, 1);
					stringstream ss; //insert line into a stringstream
					ss.str(line);
					ss >> tx;
					ss >> ty;
					x.push_back(tx);
					y.push_back(ty);
				}
			}
		}
		T mean() const {
			T ty = std::accumulate(y.begin(), y.end(), (T)0);
			return ty / y.size();
		}

		T sigma() const {
			T m = mean();
			T sum = 0.0;
			for (size_t i = 0; i < y.size(); i++)
				sum += (y.at(i) - m) * (y.at(i) - m);
			return sqrt(sum / y.size());
		}

		T median() const {
			vector<T> v = y;
			sort(v.begin(), v.end());
			T median = v[v.size()/2];
			return median;
		}

		void regression(T& slope, T& y_intercept) const {
			T tatal_xy = inner_product(x.begin(), x.end(), y.begin(), (T)0);
			T tatal_x = accumulate(x.begin(), x.end(), (T)0); //average 
			T tatal_y = accumulate(y.begin(), y.end(), (T)0); //average
			T tatal_xx = inner_product(x.begin(), x.end(), x.begin(), (T)0);
			T num = y.size();
			slope = (num * tatal_xy - tatal_x * tatal_y) / (num * tatal_xx - tatal_x * tatal_x);
			y_intercept = (tatal_y - slope * tatal_x) / num;
		}

		void display(std::ostream& os) const {
			os << setw(width) << "x";
			os << setw(width) << "y\n";
			for (size_t i = 0; i < x.size(); i++) {
				os << setw(width) << fixed << setprecision(noOfDec) << x[i] << setw(width) << y[i] << '\n';
			}
		}
	};
	template<class T>
		std::ostream& operator<<(std::ostream& os, const DataTable<T>& datatable) {
			datatable.display(os);
			return os;
		}
	
}

#endif // !_DATATABLE_H_
