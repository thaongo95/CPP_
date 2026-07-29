#ifndef SHALLOWCOPY_H
#define SHALLOWCOPY_H

#include<iostream>

class Shallow_Class{
private:
    int a;
    int b;
    int c;
public:
    Shallow_Class(){};
    Shallow_Class(int new_a, int new_b, int new_c);
    ~Shallow_Class(){
        std::cout << "happy ending !" << std::endl;
    };
    void show_class();
};

Shallow_Class::Shallow_Class(int new_a, int new_b, int new_c){
    a = new_a;
    b = new_b;
    c = new_c;
}

void Shallow_Class::show_class(){
    std::cout << "a shallow one with params list : " << a << "-" << b << "-" << c << std::endl;
    std::cout << "address of a: " << &a << std::endl;
    std::cout << "address of b: " << &b << std::endl;
    std::cout << "address of c: " << &c << std::endl;
    std::cout << std::endl;
}

#endif