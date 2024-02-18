#include "Pack.hpp"

Pack::Pack(){
    int index = 0;

    for (int suit = SPADES; suit <= DIAMONDS; ++suit){
        for (int rank = TWO; rank <= ACE; ++rank) {
            cards[index] = Card(static_cast<Rank>(rank), static_cast<Suit>(suit));
            ++index;
        }
    }
    next = 0;
}

Pack::Pack(std::istream& pack_input){
    next = 0;

    for (int index = 0; index < PACK_SIZE; ++index){
        int rank, suit; 
        pack_input >> rank >> suit;
        cards[index] = Card(static_cast<Rank>(rank), static_cast<Suit>(suit));

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
        std::array<Card, PACK_SIZE> shuffled_cards;
        int mid = PACK_SIZE/2;
        
        for (int i = 0, j = 0; i < mid; ++i, j +=2){
            shuffled_cards[j] = cards[i];
            shuffled_cards[j + 1] = cards[i + mid];
    }

    for (int i = 0; i <PACK_SIZE; ++i) {
        cards[i] = shuffled_cards[i];
    }
    }
    reset();
}

bool Pack::empty() const {
    return next >= PACK_SIZE;
}
