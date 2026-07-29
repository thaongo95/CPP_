#include "carbrand.h"

int main(){
    while (true){
        std::string brand_name;char quit;
        std::cout << "Enter the brand you want to search" << std::endl;
        getline(std::cin, brand_name);
        if (brand_name=="q" || brand_name=="quit") break;
        Carbrand brand1(brand_name);
        std::cout << "The brand " << brand_name << " have " << brand1.get_number_of_cars() << " type of cars" << std::endl;
        brand1.get_all_type_of_car();
    }
    
}