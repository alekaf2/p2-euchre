#include "Pack.hpp"
#include <cassert>
#include <iostream>
#include <array>

Pack::Pack(){
    int index = 0;

    for (int suit = SPADES; suit <= DIAMONDS; ++suit){
        for (int rank = NINE; rank <= ACE; ++rank) {
            cards[index] = Card(static_cast<Rank>(rank), static_cast<Suit>(suit));
            ++index;
        }
    }
    next = 0;
}

Pack::Pack(std::istream& pack_input){
    next = 0;

    for (int index = 0; index < PACK_SIZE; ++index){
        Card card; 
        pack_input >> card;
        cards[index] = card;
    }

}

Card Pack::deal_one(){
    //if it is an invalid rank or suit
    if (next >= PACK_SIZE){
        return Card(static_cast<Rank>(-1), static_cast<Suit>(-1));
    }
    Card next_card = cards[next];
    ++next;
    return next_card;
}

void Pack::reset(){
    next = 0;
}

void Pack::shuffle(){
    const int shuffle_iterations = 7; 
    for (int iteration = 0; iteration< shuffle_iterations; ++iteration){
        //temp array 
        std::array<Card, PACK_SIZE> temp_cards = cards;
        for (int i = 0; i < PACK_SIZE; ++i){
            if(i % 2 == 0){//in an even index
                cards.at(i) = temp_cards.at(12 + (i/2));//12 + because we want cards from the bottom half
            }else{ // in an odd index
                cards.at(i) = temp_cards.at((i - 1)/2);
            }
        }     
    }
}

bool Pack::empty() const {
    return next >= PACK_SIZE;
}
