#ifndef DEEPCOPY_H
#define DEEPCOPY_H

#include<iostream>

class Deep_Class{
private:
    int a;
    double *b = new double;
    char c;
public:
    Deep_Class(){};
    Deep_Class(int new_a, double new_b, char new_c);
    Deep_Class(Deep_Class &some_class);
    ~Deep_Class(){
        delete b;
        std::cout << "happy ending !" << std::endl;
    };
    void show_class();
};

Deep_Class::Deep_Class(int new_a, double new_b, char new_c){
    a = new_a;
    *b = new_b;
    c = new_c;
}

Deep_Class::Deep_Class(Deep_Class &some_class){
    a = some_class.a;
    b = new double;
    *b = *(some_class.b);
    c = some_class.c;
}

void Deep_Class::show_class(){
    std::cout << "a deep one with params list: " << a << "-" << *b << "-" << c << std::endl;
    std::cout << "address of a: " << &a << std::endl;
    std::cout << "address of b: " << b << std::endl;
    std::cout << "address of c: " << &c << std::endl;
    std::cout << std::endl;
}

#endif
