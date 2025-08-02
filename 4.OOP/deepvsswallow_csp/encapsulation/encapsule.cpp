#include "encapsule.h"
#include <iostream>
int Computer::counter =0;
Computer::Computer(){
    this->counter++;
}
Computer::Computer(std::string new_name, int year, int core_num){
    this->name = new_name;
    this->product_year = year;
    this->num_of_core = core_num;
    this->counter++;
}

void Computer::set_name(std::string new_name){
    this->name = new_name;
}

void Computer::set_year(int year){
    this->product_year = year;
}

void Computer::set_core_num(int num_core, bool GPU){
    this->num_of_core = num_core;
    this->GPU = GPU;
}

bool Computer::GPU_or_not(){
    return this->GPU;
}

std::string Computer::get_name(){
    return this->name;
}

int Computer::get_year(){
    return this->product_year;
}

int Computer::get_core_num(){
    return this->num_of_core;
}

void Computer::print(){
    std::cout << "com number " << counter << " name " << name <<  " producted in " << product_year << std::endl;
    if (GPU){
        std::cout << "it have " << num_of_core << " core and GPU" << std::endl;  
    }
    else{
        std::cout << "it have " << num_of_core << " core and no GPU" << std::endl;
    }
}