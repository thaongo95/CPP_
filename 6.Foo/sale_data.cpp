#include "sale_data.h"

void Sale_data::addItem(const Sale_item& item, const int& num){
	int term = findItem(item);
	if (term!=-1){
		numLists[term] += num;
		total_ += itemLists[term].getPrize()*itemLists[term].getDiscount()*num;
	}	
	else {
		itemLists.push_back(item);
		numLists.push_back(num);
		total_ += item.getPrize()*item.getDiscount()*num;
	}
	update();
}

void Sale_data::update(){
	if (itemLists.empty()){
		std::cout << "No item is added" << std::endl;
	}
	else {
		std::cout << "------ ALL the Items: " << std::endl;
		for (size_t i =0 ; i < numLists.size() ; i++){
			std::cout << "       ID: " << itemLists[i].getID() << " --- " << numLists[i] << std::endl;
		}
		std::cout << "        Total: " << total_ << std::endl;
	}
}
int Sale_data::findItem(const Sale_item& item){
	for (size_t i=0; i< itemLists.size(); i++){
		if (item.getID() == itemLists[i].getID()) return i;
	}
	return -1;
}
