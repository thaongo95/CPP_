#include <iostream>
#include <vector>
#include "sale_data.h"
#include "sale_item.h"
#include <string>


int main(){
	std::string line;
	Sale_data data;
	Sale_item item0("122NG", 20.99, 0.9);
	Sale_item item1("145fg", 40.99, 0.9);
	Sale_item item2("32ddd", 50);
	Sale_item item3("sdas1", 24);
	Sale_item item4("1221G", 25, 0.9);
	Sale_item item5("1111G", 10.99);
	data.addItem(item0, 3);
	data.addItem(item1, 2);
	data.addItem(item3, 1);
	data.addItem(item3, 3);
	data.addItem(item2, 10);
	data.addItem(item5, 3);
	data.addItem(std::string("222777"), 3);

}
