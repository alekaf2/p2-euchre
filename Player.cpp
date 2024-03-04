#include "Player.hpp"
#include <cassert>
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

std::ostream & operator<<(std::ostream &os, const Player &p) {
  assert(false);
}

class SimplePlayer : public Player {
  public:
    SimplePlayer(const std::string& name) : Player(), player_name(name) {}

    const std::string& get_name() const override {
        return player_name;
    }

    void add_card(const Card &c) override {
      assert(cards.size() <= MAX_HAND_SIZE);
      cards.push_back(c);
    }

    bool make_trump(const Card &upcard, bool is_dealer, int round, Suit &order_up_suit) const override {
      // Ensure that round is either 1 or 2
      assert(round == 1 || round == 2);

      Suit trumpSuit = upcard.get_suit();

      // Count the number of face cards (Jacks, Queens, Kings, Aces) in the player's hand that match the potential trump suit
      int count = 0;
      for (const Card &card : cards) {
          if (round == 1 && card.get_suit() == trumpSuit && card.is_face_or_ace()) {
              count++;
          } else if (round == 2 && card.get_suit() == Suit_next(trumpSuit) && card.is_face_or_ace()) {
              // If it's the second round and the player has a face card in the next suit, they must order up
              // So, we can return true immediately
              return true;
          }
      }

      // If it's the first round and the player has at least two face cards in the potential trump suit,
      // they can order up the trump suit
      if (round == 1 && count >= 2) {
          order_up_suit = trumpSuit;
          return true;
      } else if (round == 2 && is_dealer) {
          // If it's the second round and the player is the dealer, they must order up the next suit
          order_up_suit = Suit_next(trumpSuit);
          return true;
      }

      // If none of the above conditions are met, the player cannot order up and must pass
      return false;
  };



    void add_and_discard(const Card &upcard) override {
      // Ensure that the player has at least one card in their hand
      assert(cards.size() > 0);

      // Add the upcard to the player's hand
      add_card(upcard);

      // Find the smallest card in the player's hand and remove it
      Card min = cards[0];    
      int minIndex = 0;       
      for (size_t i = 0; i < cards.size(); i++) {
          if (cards[i] < min) {    
              min = cards[i];      
              minIndex = i;        
          }
      }

      // Remove the smallest card from the player's hand
      cards.erase(cards.begin() + minIndex);
  }

    Card lead_card(Suit trump) override {
      // Ensure that the player has at least one card in their hand
      assert(cards.size() > 0);

      int nonTrumpIndex = 0;  
      Card topCard;           

      // Iterate through the player's hand to find the highest non-trump card
      for (size_t i = 0; i < cards.size(); i++) {
          if (cards[i].get_suit() != trump) {  
              if (nonTrumpIndex == 0) {        
                  topCard = cards[i];          
              } else {
                  if (cards[i] > topCard) {     
                      topCard = cards[i];       
                  }
              }
              nonTrumpIndex++;  
          }
      }

      // If no non-trump card was found, find the highest trump card in the hand
      if (nonTrumpIndex == 0) {
          topCard = cards[0];
          for (size_t j = 0; j < cards.size(); j++) {
              if (cards[j] > topCard) {
                  topCard = cards[j];
              }
          }
      }

      // Remove the top card from the player's hand
      for (size_t k = 0; k < cards.size(); k++) {
          if (cards[k] == topCard) {
              cards.erase(cards.begin() + k);
              break; 
          }
      }

      return topCard;
  };

    Card play_card(const Card &led_card, Suit trump) override {
      // Ensure that the player has at least one card in their hand
      assert(cards.size() > 0);

      Card cardToPlay = cards[0];  

      // Iterate through the player's hand to find the card to play
      for (size_t i = 0; i < cards.size(); i++) {
          if (cards[i].get_suit() == led_card.get_suit()) {  // Check if the card is of the led suit
              if (cards[i] > cardToPlay) {  // If the current card is higher than the current card to play
                  cardToPlay = cards[i];       
              }
          }
      }

      // If no card of the led suit was found, play the lowest card in hand
      if (cardToPlay.get_suit() != led_card.get_suit()) {
          cardToPlay = cards[0];
          for (size_t i = 1; i < cards.size(); i++) {
              if (cards[i] < cardToPlay) {
                  cardToPlay = cards[i];
              }
          }
      }

      // Remove the card to play from the player's hand
      cards.erase(std::remove(cards.begin(), cards.end(), cardToPlay), cards.end());

      return cardToPlay;  // Return the card to play
  };

private:
    const std::string& player_name;
    std::vector<Card> cards;
};

class HumanPlayer : public Player {
  public: 
    HumanPlayer(const std::string& name) : Player(), player_name(name) {};

    const std::string& get_name() const override {
        return player_name;
    };

    void add_card(const Card &c) override {
      assert(cards.size() < MAX_HAND_SIZE);
      cards.push_back(c);
    };

    bool make_trump(const Card &upcard, bool is_dealer,
        int round, Suit &order_up_suit) const override{
          // Checks if its Round 1 or 2
          assert(round == 1 || round == 2);
          print_hand();
          std::string orderUpChoice = "";
          std::cout << "Human player " << player_name << ", please enter a suit, or \"pass\":\n";
          std:: cin >> orderUpChoice;

          if (orderUpChoice != "pass"){
            order_up_suit = string_to_suit(orderUpChoice);
            return true;
          }
          else{
            return false;  
          }
    };

    void add_and_discard(const Card &upcard) override{
      // Checks to make sure there is at least 1 card in the deck
      assert(cards.size() > 0);
      
      print_hand();
      int discardChoice;
      std::cout << "Discard upcard: [-1]\n";
      std::cout << "Human player " << player_name << ", please select a card to discard:\n";
      std::cin >> discardChoice;
      // Only edits the deck if the upcard is not removed
      if (discardChoice != -1){
        cards.erase(cards.begin() + discardChoice);
        add_card(upcard);
        std::sort(cards.begin(), cards.end());
      }
    };

    Card lead_card(Suit trump) override{
      // Checks to make sure there is at least 1 card in the deck
      assert(cards.size() > 0);
      print_hand();
      int lead_card_index;
      std::cout << "Human player " << player_name << ", please select a card:\n";
      std::cin >> lead_card_index;
      return cards[lead_card_index];
      cards.erase(cards.begin() + lead_card_index);
    };

    Card play_card(const Card &led_card, Suit trump) override{
      // Checks to make sure there is at least 1 card in the deck
      assert(cards.size() > 0);
      print_hand();
      int play_card_index;
      std::cout << "Human player " << player_name << ", please select a card:\n";
      std::cin >> play_card_index;
      return cards[play_card_index];
      cards.erase(cards.begin() + play_card_index);
    };
  
  private:
    const std::string& player_name;
    std::vector<Card> cards;

    void print_hand() const {
      for (size_t i=0; i < cards.size(); ++i){
        std::cout << "Human player " << player_name << "'s hand: "
          << "[" << i << "] " << cards[i] << "\n";
      }
    }


};

Player * Player_factory(const std::string &name, 
                        const std::string &strategy) {
  // We need to check the value of strategy and return 
  // the corresponding player type.
  if (strategy == "Simple") {
    // The "new" keyword dynamically allocates an object.
    return new SimplePlayer(name);
  }
  // Repeat for each other type of Player
  else if (strategy == "Human") {
    return new HumanPlayer(name);
  }
  // Invalid strategy if we get here
  assert(false);
  return nullptr;
}
