#include "thao.h"

Thao::Thao(int i){
    bank_acount=i;
}

int Thao::get_money(){
    return bank_acount;
}


void friend_func(Thao &thao){
    std::cout << "cureent money: "  << thao.bank_acount << std::endl;
}