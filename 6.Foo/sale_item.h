#ifndef SALE_ITEM_H
#define SALE_ITEM_H
#include <string>

class Sale_item{
public:
	Sale_item(const std::string& id);
	Sale_item(const std::string& id, const double& prize);
	Sale_item(const std::string& id, const double& prize, const double& discount);
	Sale_item(const Sale_item& sale_item);
	~Sale_item();
	std::string getID() const {return id_;}
	double getPrize() const {return prize_;}
	double getDiscount() const {return discount_;}
	
	void setPrize(const double& prize);
	void setDiscount(const double& discount);
private:
	std::string id_;
	double prize_;
	double discount_;	
		
};
#endif 
