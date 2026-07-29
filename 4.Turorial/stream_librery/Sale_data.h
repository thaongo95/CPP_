#pragma once
#include <string>
#include <vector>
class Sale_data {
	std::vector <std::string> items;
	std::vector <int> numbers;
	std::vector <double> prices;
	//double total{ 0 };
public:
	void setItem(const std::string& item)
	{
		items.push_back(item);
	}
	void setNumber(const int& num) {
		numbers.push_back(num);
	}
	void setPrice(const double& price) {
		prices.push_back(price * 1.0);
	}
	double getTotal() const {
		double total{ 0 };
		for (int i{ 0 }; i < items.size(); i++) {
			total += numbers[i] * prices[i] * 1.0;
		}
		return total;
	}
	bool operator>(const Sale_data& other) {
		return getTotal() > other.getTotal();
	}
};