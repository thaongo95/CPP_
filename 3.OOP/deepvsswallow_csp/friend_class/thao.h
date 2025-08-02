#ifndef THAO_H
#define THAO_H

#include<iostream>
#include<string>
class Thao{
    int bank_acount{100};
    friend class Thang;
    friend void friend_func(Thao &thao);
    public:
        Thao(){};
        Thao(int i);
        int get_money();
}; //create an instance

#endif