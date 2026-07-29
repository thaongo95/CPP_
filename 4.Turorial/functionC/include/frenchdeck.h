#ifndef FRENCHDECK_H
#define FRENCHDECK_H
#include <vector>
#include <string>
#include "card.h"
class FrenchDeck{
    public:
        std::vector<char> ranks = {'1', '2', '3', '4', '5', '6', '7', '8', '9', '1', 'J', 'Q', 'K', 'A'};
        std::vector<std::string> suits;
        std::vector<Card> cards;
    public:
        void create_cards();
        void show_card();
        void get_card_value();
};





#endif