#include "carbrand.h"


Carbrand::Carbrand(std::string brand_name){
    this->brand_name=brand_name;
}

void Carbrand::get_all_type_of_car(){
    if (brand_name=="hyundai"){
        for (auto car:hyundai){
            std::cout << "###########" << car << "############" << std::endl;
        }
    }
    else if (brand_name =="honda")
    {
        for (auto car:honda){
            std::cout << "###########" << car << "############" << std::endl;
        }
    }
    else if (brand_name =="toyota")
    {
        for (auto car:toyota){
            std::cout << "###########" << car << "############" << std::endl;
        }
    }
    else if (brand_name =="ford")
    {
        for (auto car:ford){
            std::cout << "###########" << car << "############" << std::endl;
        }
    }
    else if (brand_name =="kia")
    {
        for (auto car:kia){
            std::cout << "###########" << car << "############" << std::endl;
        }
    }
    else{
        std::cout << "The brand have not recorded" << std::endl;
    }
}

int Carbrand::get_number_of_cars(){
    if (brand_name=="hyundai"){
        return hyundai.size();
    }
    else if (brand_name =="honda")
    {
        return honda.size();
    }
    else if (brand_name =="toyota")
    {
        return toyota.size();
    }
    else if (brand_name =="ford")
    {
        return ford.size();
    }
    else if (brand_name =="kia")
    {
        return kia.size();
    }
    else{
        return 0;
    }
}
