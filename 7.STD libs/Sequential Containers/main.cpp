#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <numeric>
#include <algorithm>

struct Item{
	Item(std::string& a, double b, int c): name{a}, prize{b}, number{c} {}
	std::string name;
	double prize;
	int number;
};

class Customer_data{
	public:
		void updateInfo(const std::string& file);
		double getTotal(){return sended_amount;}
		void print();
	private:
		std::vector<Item> items;
		double sended_amount{0};
};

void Customer_data::updateInfo(const std::string& file){
	std::ifstream read(file);
	std::string line;
	while(getline(read, line)){
		std::stringstream ss(line);
		std::string arg1, arg2, arg3;
		if (ss >> arg1 >> arg2 >> arg3){
			//items.push_back(Item(arg1, std::stod(arg2),std::stoi(arg3)));
			items.emplace_back(arg1, std::stod(arg2),std::stoi(arg3));
			sended_amount += std::stod(arg2)*std::stoi(arg3);
			 
		}
	}
}

void Customer_data::print(){
	for (auto it = items.cbegin();it!=items.cend(); it++){
		std::cout << (*it).name << " " ;
	}
	std::cout << std::endl;
	std::cout << "Total: " << sended_amount << std::endl;
}
int main(int argc, char** argv){
        std::vector<int> vt1 = {1,2,3,4,5,6,7};
        std::vector<double> vt2 = {2,3,4,5,6,7};
        auto temp = std::find(vt1.begin(), vt1.end(), 2);
        if (temp!=vt1.end()){
        	*temp = 99;
        	//std::cout << *temp << std::endl;
        }
        
        //std::swap(vt1,vt2);
        vt1.insert(vt1.begin()+3, 10, 100);
        //vt1.assign(vt2.begin(), vt2.end()-2);
        for (auto vt:vt1) std::cout << vt << " ";
        std::cout << std::endl;
        for (auto vt:vt2) std::cout << vt << " ";
        std::cout << std::endl;
	Customer_data person1;
	person1.updateInfo("text.txt");
	person1.print();
	std::cout << person1.getTotal() <<std::endl;
	return 0;
}
