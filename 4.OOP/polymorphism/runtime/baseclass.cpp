#include "baseclass.h"


void Baseclass::function1(){
    std::cout << "this is function1 of the Parent class" << std::endl;
}

void Baseclass::function2(){
    std::cout << "this is function2 of the Parent class" << std::endl;
}

void Shape::get_area(){
    std::cout << "Calculation the Shape Area" << std::endl;
}