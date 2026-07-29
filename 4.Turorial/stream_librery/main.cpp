#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "Sale_data.h"

int main() {
	
	std::ifstream fin("input.txt");
	std::ofstream fout("output.txt");
	std::string str;
	while (std::getline(fin, str)) {
		fout << str << std::endl;
		fout << "**********************************" << std::endl;
	}
	
	fout << "finished! " << std::endl;

	std::ifstream input_data{ "Sale1.txt" };
	Sale_data sale_date1;
	std::string data_str;

	while (std::getline(input_data, data_str)) {
		std::istringstream str_stream(data_str);
		
		std::string item, number, price;
		str_stream >> item >> number >> price;
		sale_date1.setItem(item);
		sale_date1.setNumber(stoi(number));
		sale_date1.setPrice(stod(price));
		
	}

	std::ifstream input_data2{ "Sale2.txt" };
	Sale_data sale_date2;
	std::string data_str2;
	while (std::getline(input_data2, data_str2)) {
		std::istringstream str_stream(data_str2);
		std::string item, number, price;
		str_stream >> item >> number >> price;
		sale_date2.setItem(item);
		sale_date2.setNumber(stoi(number));
		sale_date2.setPrice(stod(price));

	}
	
	std::cout << std::endl;

	std::ostringstream firstline;
	std::ostringstream secondline;
	std::ostringstream thirdline;
	std::ostringstream fourline;
	firstline << "tran 1 sum : " << sale_date1.getTotal() << "; tran 2 sum : " << sale_date2.getTotal() << std::endl;
	secondline << "***************************************" << std::endl;
	thirdline << "Which transaction is bigger ?" << std::endl;
	fourline << ((sale_date1 > sale_date2) ? "Result: Transaction 1" : "Result: Transaction 2") << std::endl;
	std::cout << firstline.str() << secondline.str() << thirdline.str() << fourline.str();

	std::cout << std::endl;

	std::cout << "which file is open ?" << std::endl;
	std::cout << "output.txt : " << ((fout) ? "true" : "false") << std::endl;
	std::cout << "input.txt : " << ((fin) ? "true" : "false") << std::endl;
	std::cout << "Sale1.txt : " << ((input_data) ? "true" : "false") << std::endl;
	std::cout << "Sale2.txt : " << ((input_data2) ? "true" : "false") << std::endl;

	std::cout << std::endl;
	std::string buffer;
	while (std::getline(input_data, buffer)) {
		std::cout << buffer << std::endl;
	}

}