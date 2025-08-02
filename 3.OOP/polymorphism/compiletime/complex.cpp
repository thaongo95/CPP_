#include "complex.h"

Complex::Complex(int x, int y, int z){
    this->x=x;
    this->y=y;
    this->z=z;
}

Complex Complex::operator+(Complex const& other){
    Complex comp;
    comp.x = x + other.x;
    comp.y = y + other.y;
    comp.z = z + other.z;
    return comp;
}
Complex Complex::operator*(Complex const& other){
    Complex comp;
    comp.x = x * other.x;
    comp.y = y * other.y;
    comp.z = z * other.z;
    return comp;
}
void Complex::func(int x){
    std::cout << x << std::endl;
}
void Complex::func(int x, int y){
    std::cout << x+y << std::endl;
}
void Complex::func(int x, int y, int z){
    std::cout << x+y+z << std::endl;
}
void Complex::print(){
    std::cout << "Complex(x: " << x << " y: " << y  << " z: " << z << ")" << std::endl;
}