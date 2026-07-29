#include "include/frenchdeck.h"
#include "sources/overloading_func.cpp"
#include "sources/string_functions.cpp"

void over_loading(){
    std::cout << "mul of two int: " << mul(2, 4) << std::endl;
    std::cout << "mul of two double: " << mul(2.3, 4.5) << std::endl;
    std::cout << "mul of three double: " << mul(2.3, 4.5, 6.5) << std::endl;
    int x{12}, y{32}, z{32};
    std::vector<double> arr = {23.3232, 334.232323, 32.32323};
    increment(&x);
    increment(&y);
    increment(&z);
    for (int i=0; i< arr.size();i++){
        increment(&arr[i]);
    }
    std::cout << "Increment: " << x << '-' << y << '-' << z<< std::endl;
    for (auto a:arr){
        std::cout <<  a << " ";
    }
    std::cout << std::endl;
    bigandsmall param;
    compare_num(13, 45, param);
    std::cout << "big : " << param.big << std::endl;
    std::cout << "small: " << param.small << std::endl;
    std::vector<int> abc = {12,23,12,32,34,65,43,54,34,32,12,45};
    compare_num(abc, param);
    std::cout << "biggest : " << param.big << std::endl;
    std::cout << "smallest: " << param.small << std::endl;
}

int main(){

    // ~ created a frenchdeck instance and show all of 52 cards
    FrenchDeck deck;
    deck.create_cards();
    // deck.show_card();

    over_loading();
    
}