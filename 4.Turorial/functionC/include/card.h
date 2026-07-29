#ifndef CARD_H
#define CARD_H
#include <string>
#include <iostream>
class Card
{    
    public:
        char rank;
        std::string suit;
        void print_card(){
            std::cout << rank << " " << suit << std::endl;
        }
        void set_rank(char new_rank){
            Card::rank = new_rank;
        }
        void set_suit(std::string new_suit){
            Card::suit = new_suit;
        }
};


#endif