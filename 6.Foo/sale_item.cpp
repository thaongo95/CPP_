#include "sale_item.h"

Sale_item::Sale_item(const std::string& id)
	: id_{id}, prize_{0}, discount_{1}
{
	
}
Sale_item::Sale_item(const std::string& id, const double& prize)
	: id_{id}, prize_{prize}, discount_{1}
{
	
}
Sale_item::Sale_item(const std::string& id, const double& prize, const double& discount)
	: id_ {id}, prize_ {prize}, discount_{discount}
{
	
}
Sale_item::Sale_item(const Sale_item& sale_item)
{
	id_ = sale_item.getID();
	prize_ = sale_item.getPrize();
	discount_ = sale_item.getDiscount();
}
Sale_item::~Sale_item(){}
