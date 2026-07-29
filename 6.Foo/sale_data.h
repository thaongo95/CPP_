#ifndef SALE_DATA_H
#define SALE_DATA_H

#include <iostream>
#include <vector>
#include "sale_item.h"
class Sale_data{
public:
	void addItem(const Sale_item& item, const int& num);
	
	double getTotal() {return total_;}
private:
	std::vector<Sale_item> itemLists;
	std::vector<int> numLists;
	double total_=0;
private:
	void update();
	int findItem(const Sale_item& item);	
};



#endif 
