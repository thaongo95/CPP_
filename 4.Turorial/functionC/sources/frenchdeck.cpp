#include "frenchdeck.h"

void FrenchDeck::create_cards(){    
    suits.push_back("spides");
    suits.push_back("diamonds");
    suits.push_back("hearts");
    suits.push_back("clubs");
    for (auto rank: ranks){
        for (auto suit: suits){
            Card card;
            card.set_rank(rank);
            card.set_suit(suit);
            FrenchDeck::cards.push_back(card);
        }
    }
}

void FrenchDeck::show_card(){
    for (auto card:FrenchDeck::cards){
        std::cout << "Card: " << card.rank << " " << card.suit << std::endl;
    }
}

