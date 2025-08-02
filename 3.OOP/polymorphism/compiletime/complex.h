
#include <iostream>
// COMPLIE_TIME Polymorphism is achieved by function overloading or operator overloading

class Complex{
    int x,y,z;
    public:
        Complex(){};
        Complex(int x, int y, int z);
        Complex operator+(Complex const& other);
        Complex operator*(Complex const& other);
        void func(int x);
        void func(int x, int y);
        void func(int x, int y, int z);
        void print();
};