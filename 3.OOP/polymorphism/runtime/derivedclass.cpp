
#include "derivedclass.h"

void Derived_1::function1(){
    std::cout << "this is function1 of child 1" << std::endl;
}

void Derived_2::function1(){
    std::cout << "this is function1 of child 2" << std::endl;
}

void Derived_3::function1(){
    std::cout << "this is function1 of child 3" << std::endl;
}

void Derived_4::function1(){
    std::cout << "this is function1 of child 4" << std::endl;
}

void Derived_1::function2(){
    std::cout << "this is function2 of child 1" << std::endl;
}

void Derived_2::function2(){
    std::cout << "this is function2 of child 2" << std::endl;
}

void Derived_3::function2(){
    std::cout << "this is function2 of child 3" << std::endl;
}

void Derived_4::function2(){
    std::cout << "this is function2 of child 4" << std::endl;
}

Rectangle::Rectangle(int width, int height){
    this->width = width;
    this->height = height;
}

void Rectangle::get_area(){
    std::cout << "Area: " << width*height << std::endl;
}

Tritangle::Tritangle(int bottom, int height){
    this->bottom = bottom;
    this->height = height;
}

void Tritangle::get_area(){
    std::cout << "Area: " << bottom*height/2 << std::endl;
}

Circle::Circle(int R){
    this->R = R;
}

void Circle::get_area(){
    std::cout << "Area: " << R*R*Pi << std::endl;
}