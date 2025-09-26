#include <iostream>
#include <vector>
#include <algorithm>
#include <memory>


class Investment{
	public:
		Investment(double time, double money, double percentage): life_time{time}, base_money{money}, percent_of_benefit{percentage}{}
		virtual void get_total_money(){
			std::cout << "Total : " << base_money*((double)(life_time/365)*percent_of_benefit) << " $" << std::endl;
		}
	virtual ~Investment(){std::cout << "Investment out" << std::endl;}
	protected:
		double life_time{0};
		double base_money{0};
		double percent_of_benefit{1};
	
};
class Stock: public Investment{
public:
	Stock(double time, double money, double percentage): Investment(time, money, percentage){}	
	
	void get_total_money() override{
		std::cout << "Stock : " << base_money*(life_time/365*percent_of_benefit) << " $" << std::endl;
	}
	virtual ~Stock(){std::cout << "Stock out" << std::endl;}
};

class Bond: public Investment{
public:
	Bond(double time, double money, double percentage): Investment(time, money, percentage){}
	
	void get_total_money() override{
		std::cout << "Bond : " << base_money*(life_time/365*percent_of_benefit) << " $" << std::endl;
	}
	virtual ~Bond() override{std::cout << "Bond out" << std::endl;}
};
class RealEstate: public Investment{
public:
	RealEstate(double time, double money, double percentage): Investment(time, money, percentage){}
	
	void get_total_money() override{
		std::cout << "RealEstate : " << base_money*(life_time/365*percent_of_benefit) << " $" << std::endl;
	}
	virtual ~RealEstate() override{std::cout << "RealEstate out" << std::endl;}
};




int main(){
	std::unique_ptr<Investment> invest = std::make_unique<Bond>(150,1000000,1.05);
	invest->get_total_money();
	auto bond = std::make_unique<Bond>(365,100000,1.05);
	bond->get_total_money();
	return 0;
}
