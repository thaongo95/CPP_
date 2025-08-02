#ifndef THANG_H
#define THANG_H

#include "thao.h"
class Thang{
    int bank_acount;
    friend void friend_func(Thang &thang);
    public:
        Thang(){};
        Thang(int money){
            bank_acount = money; 
        };
        ~Thang(){};
        void getfromthao(Thao &thao, int amout){
            thao.bank_acount -= amout;
            bank_acount += amout;
        }
        int get_money(){
            return bank_acount;
        }
};
void friend_func(Thang &thang){
    std::cout << "cureent money: "  << thang.bank_acount << std::endl;
}
#endif