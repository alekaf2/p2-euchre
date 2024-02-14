#include <cassert>
#include <iostream>
#include <array>
#include "Card.hpp"

using namespace std;

/////////////// Rank operator implementations - DO NOT CHANGE ///////////////

constexpr const char *const RANK_NAMES[] = {
  "Two",   // TWO
  "Three", // THREE
  "Four",  // FOUR
  "Five",  // FIVE
  "Six",   // SIX
  "Seven", // SEVEN
  "Eight", // EIGHT
  "Nine",  // NINE
  "Ten",   // TEN
  "Jack",  // JACK
  "Queen", // QUEEN
  "King",  // KING
  "Ace"    // ACE

};
//REQUIRES str represents a valid rank ("Two", "Three", ..., "Ace")
//EFFECTS returns the Rank correspoinding to str, for example "Two" -> TWO
Rank string_to_rank(const std::string &str) {
  for(int r = TWO; r <= ACE; ++r) {
    if (str == RANK_NAMES[r]) {
      return static_cast<Rank>(r);
    }
  }
  assert(false); // Input string didn't match any rank
  return {};
}

//EFFECTS Prints Rank to stream, for example "Two"
std::ostream & operator<<(std::ostream &os, Rank rank) {
  os << RANK_NAMES[rank];
  return os;
}

//REQUIRES If any input is read, it must be a valid rank
//EFFECTS Reads a Rank from a stream, for example "Two" -> TWO
std::istream & operator>>(std::istream &is, Rank &rank) {
  string str;
  if(is >> str) {
    rank = string_to_rank(str);
  }
  return is;
}



/////////////// Suit operator implementations - DO NOT CHANGE ///////////////

constexpr const char *const SUIT_NAMES[] = {
  "Spades",   // SPADES
  "Hearts",   // HEARTS
  "Clubs",    // CLUBS
  "Diamonds", // DIAMONDS
};

//REQUIRES str represents a valid suit ("Spades", "Hearts", "Clubs", or "Diamonds")
//EFFECTS returns the Suit correspoinding to str, for example "Clubs" -> CLUBS
Suit string_to_suit(const std::string &str) {
  for(int s = SPADES; s <= DIAMONDS; ++s) {
    if (str == SUIT_NAMES[s]) {
      return static_cast<Suit>(s);
    }
  }
  assert(false); // Input string didn't match any suit
  return {};
}

//EFFECTS Prints Suit to stream, for example "Spades"
std::ostream & operator<<(std::ostream &os, Suit suit) {
  os << SUIT_NAMES[suit];
  return os;
}

//REQUIRES If any input is read, it must be a valid suit
//EFFECTS Reads a Suit from a stream, for example "Spades" -> SPADES
std::istream & operator>>(std::istream &is, Suit &suit) {
  string str;
  if (is >> str) {
    suit = string_to_suit(str);
  }
  return is;
}



/////////////// Write your implementation for Card below ///////////////


// NOTE: We HIGHLY recommend you check out the operator overloading
// tutorial in the project spec before implementing
// the following operator overload functions:
//   operator<<
//   operator>>
//   operator<
//   operator<=
//   operator>
//   operator>=
//   operator==
//   operator!=

Card::Card()
: rank(TWO), suit(SPADES) {}

Card::Card(Rank rank_in, Suit suit_in)
: rank(rank_in), suit(suit_in) {}

Rank Card::get_rank() const{
  return rank;
}

Suit Card::get_suit() const{
  return suit;
}

Suit Card::get_suit(Suit trump) const{
 if (is_left_bower(trump)) {
  return trump;
 } 
 else {
  return suit;
 }
}

bool Card::is_face_or_ace() const {
  return (rank == JACK || rank == QUEEN || rank == KING || rank == ACE);
}

bool Card::is_right_bower(Suit trump) const {
  return (rank == JACK && suit == trump);
}

bool Card::is_left_bower(Suit trump) const {
  Suit nextSuit = Suit_next(trump);
  return (rank == JACK && suit == nextSuit);
}

bool Card::is_trump(Suit trump) const {
  return (suit == trump || is_left_bower(trump));
}


bool operator<(const Card &lhs, const Card &rhs){
  if(lhs.get_rank() == rhs.get_rank()) {
    return lhs.get_suit() < rhs.get_suit();
  }else{  
    return lhs.get_rank() < rhs.get_rank();
  }
}

bool operator<=(const Card &lhs, const Card &rhs){
  if(lhs.get_rank() == rhs.get_rank()) {
    return lhs.get_suit() <= rhs.get_suit();
  }else{  
    return lhs.get_rank() <= rhs.get_rank();
  } 
}

bool operator>(const Card &lhs, const Card &rhs){ //Card a > Card b
//compare rank
if(lhs.get_rank() == rhs.get_rank()) {
  return lhs.get_suit() > rhs.get_suit();
}else{  
  return lhs.get_rank() > rhs.get_rank();
}
}
bool operator>=(const Card &lhs, const Card &rhs){
if(lhs.get_rank() == rhs.get_rank()) {
  return lhs.get_suit() >= rhs.get_suit();
}else{  
  return lhs.get_rank() >= rhs.get_rank();
}
}

bool operator==(const Card &lhs, const Card &rhs){
if(lhs.get_rank() == rhs.get_rank()) {
  return lhs.get_suit() == rhs.get_suit();
}else{  
  return lhs.get_rank() == rhs.get_rank();
}
}

bool operator!=(const Card &lhs, const Card &rhs){
if(lhs.get_rank() == rhs.get_rank()) {
  return lhs.get_suit() != rhs.get_suit();
}else{  
  return lhs.get_rank() != rhs.get_rank();
}
}

 Suit Suit_next(Suit suit){
  const Suit nextSuits[]= {CLUBS, DIAMONDS, SPADES, HEARTS};
  return nextSuits[suit];
}

bool Card_less(const Card &a, const Card &b, Suit trump){
  if(a.is_trump(trump) && !b.is_trump(trump)){
    return false;
  }
    else if (!a.is_trump(trump) && b.is_trump(trump)) {
      return true;
    } 
    return (a.get_rank() < b.get_rank()); //if both a and b are trump or not look at rank
}

bool Card_less(const Card &a, const Card &b, const Card &led_card, Suit trump){
  // Check if one of the cards is a trump card and the other is not
   if (a.is_trump(trump) && !b.is_trump(trump)) {
      return true;  
  } else if (!a.is_trump(trump) && b.is_trump(trump)) {
      return false;  
  }
    // If both are trump or not
    // compare based on rank and the suit led
  if (a.get_suit(trump) == led_card.get_suit(trump) && b.get_suit(trump) == led_card.get_suit(trump)) {
      return (a.get_rank() < b.get_rank());  // suits the same check rank
  } else if (a.get_suit(trump) == led_card.get_suit(trump)) {
      return true;  // Return true if a has the same suit as the one led
  } else if (b.get_suit(trump) == led_card.get_suit(trump)) {
      return false;  // Return false if b has the same suit as the one led
  }
// suits led different look at rank only
  return (a.get_rank() < b.get_rank());

}