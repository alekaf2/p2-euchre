#include "Player.hpp"
#include "unit_test_framework.hpp"
#include <sstream>
#include <iostream>

using namespace std;

TEST(test_player_get_name) {
    Player * alice = Player_factory("Alice", "Simple");
    ASSERT_EQUAL("Alice", alice->get_name());

    delete alice;
}

// Add more tests here
TEST(test_simple_player_make_trump) {
  // Joe's hand
  Player * joe = Player_factory("Joe", "Simple");
  joe->add_card(Card(NINE, CLUBS));
  joe->add_card(Card(KING, HEARTS));
  joe->add_card(Card(JACK, CLUBS));
  joe->add_card(Card(QUEEN, HEARTS));
  joe->add_card(Card(KING, SPADES));

  // Joe makes trump
  Card ten_hearts(TEN, HEARTS);
  Suit trump;
  bool orderup = joe->make_trump(
    ten_hearts,     // Upcard
    false,          // Joe is not the dealer
    1,              // First round
    trump           // Suit ordered up (if any)
  );

  // Verify Joe's order up (should be true with HEARTS as trump suit)
  ASSERT_TRUE(orderup);
  ASSERT_EQUAL(trump, HEARTS);

  delete joe;
}

TEST(test_simple_player_make_trump1) {
  // Joe's hand
  Player * joe = Player_factory("Joe", "Simple");
  joe->add_card(Card(NINE, CLUBS));
  joe->add_card(Card(KING, CLUBS));
  joe->add_card(Card(JACK, CLUBS));
  joe->add_card(Card(QUEEN, CLUBS));
  joe->add_card(Card(TEN, HEARTS));

  // Joe makes trump
  Card ten_clubs(TEN, CLUBS);
  Suit trump;
  bool orderup = joe->make_trump(
    ten_clubs,     // Upcard
    false,          // Joe is not the dealer
    1,              // First round
    trump           // Suit ordered up (if any)
  );

  // Verify Joe's order up (should be true with HEARTS as trump suit)
  ASSERT_TRUE(orderup);
  ASSERT_EQUAL(trump, CLUBS);

  delete joe;
}

TEST(test_simple_player_make_trump3) {
  // Joe's hand
  Player * joe = Player_factory("Joe", "Simple");
  joe->add_card(Card(NINE, CLUBS));
  joe->add_card(Card(KING, CLUBS));
  joe->add_card(Card(JACK, CLUBS));
  joe->add_card(Card(QUEEN, CLUBS));
  joe->add_card(Card(TEN, SPADES));

  // Joe makes trump
  Card nine_spades(TEN, CLUBS);
  Suit trump;
  bool orderup = joe->make_trump(
    nine_spades,     // Upcard
    true,          // Joe is not the dealer
    2,              // First round
    trump           // Suit ordered up (if any)
  );

  // Verify Joe's order up (should be true with HEARTS as trump suit)
  ASSERT_TRUE(orderup);
  ASSERT_EQUAL(trump, SPADES);

  delete joe;
}

TEST(test_simple_player_make_trump4) {
    // Alice's hand
    Player * alice = Player_factory("Alice", "Simple");
    alice->add_card(Card(NINE, DIAMONDS));
    alice->add_card(Card(TEN, CLUBS));
    alice->add_card(Card(JACK, CLUBS));
    alice->add_card(Card(QUEEN, DIAMONDS));
    alice->add_card(Card(KING, SPADES));

    // Alice makes trump
    Card ten_hearts(TEN, HEARTS);
    Suit trump;
    bool orderup = alice->make_trump(
        ten_hearts,     // Upcard
        false,          // Alice is not the dealer
        1,              // First round
        trump           // Suit ordered up (if any)
    );

    // Verify Alice didn't order up
    ASSERT_FALSE(orderup);

    delete alice;
}

TEST(test_simple_player_make_trump5) {
  // Joe's hand
  Player * joe = Player_factory("Joe", "Simple");
  joe->add_card(Card(NINE, HEARTS));
  joe->add_card(Card(KING, HEARTS));
  joe->add_card(Card(JACK, HEARTS));
  joe->add_card(Card(QUEEN, HEARTS));
  joe->add_card(Card(TEN, HEARTS));

  // Joe makes trump
  Card ace_hearts(ACE, HEARTS);
  Suit trump;
  bool orderup = joe->make_trump(
    ace_hearts,     // Upcard
    true,          // Joe is not the dealer
    2,              // First round
    trump           // Suit ordered up (if any)
  );

  // Verify Joe's order up (should be true with HEARTS as trump suit)
  ASSERT_TRUE(orderup);
  ASSERT_EQUAL(trump, DIAMONDS);

  delete joe;
}

TEST(test_simple_player_lead_card) {
  // Joe's hand
  Player *joe = Player_factory("Joe", "Simple");
  joe->add_card(Card(NINE, SPADES));   
  joe->add_card(Card(TEN, SPADES));    
  joe->add_card(Card(QUEEN, SPADES));  
  joe->add_card(Card(KING, SPADES));   
  joe->add_card(Card(ACE, SPADES));   

  Suit trump = SPADES;                 // Set SPADES as the trump suit
  Card ace_spades = Card(ACE, SPADES); // Create a Card representing the Ace of Spades
  // Verify that Joe leads with the Ace of Spades
  ASSERT_EQUAL(joe->lead_card(trump), ace_spades);

  delete joe;                          
}
TEST(test_simple_player_lead_card1) {
  // Joe's hand
  Player * joe = Player_factory("Joe", "Simple");
  joe->add_card(Card(NINE, HEARTS));
  joe->add_card(Card(TEN, CLUBS));
  joe->add_card(Card(QUEEN, HEARTS));
  joe->add_card(Card(KING, DIAMONDS));
  joe->add_card(Card(ACE, DIAMONDS));

  Suit trump = DIAMONDS;              // Set DIAMONDS as the trump suit
  Card queen_hearts = Card(QUEEN, HEARTS); // Create a card represnting the Queen of Hearts
  // Verify that Joe leads with the queen of hearts
  ASSERT_EQUAL(joe->lead_card(trump), queen_hearts);

  delete joe;
}

TEST(test_simple_player_lead_card2) {
  // Joe's hand
  Player * joe = Player_factory("Joe", "Simple");
  joe->add_card(Card(NINE, HEARTS));
  joe->add_card(Card(TEN, CLUBS));
  joe->add_card(Card(QUEEN, HEARTS));
  joe->add_card(Card(KING, DIAMONDS));
  joe->add_card(Card(ACE, DIAMONDS));

  Suit trump = SPADES;              // Set SPADES as the trump suit
  Card ace_diamonds = Card(ACE, DIAMONDS); // Create a card representing the Ace of Diamonds
  // Verify that Joe led with the Ace of Diamonds
  ASSERT_EQUAL(joe->lead_card(trump), ace_diamonds);

  delete joe;
}

TEST(test_simple_player_lead_card3) {
  // Joe's hand
  Player * joe = Player_factory("Joe", "Simple");
  joe->add_card(Card(NINE, CLUBS));
  joe->add_card(Card(TEN, HEARTS));
  joe->add_card(Card(QUEEN, HEARTS));
  joe->add_card(Card(KING, HEARTS));
  joe->add_card(Card(ACE, HEARTS));

  Suit trump = HEARTS;               // Set HEARTS as the trump suit
  Card nine_clubs = Card(NINE, CLUBS); // Create a card representing the Nine of Clubs
  // Verify that Joe leads with the Nine of Clubs
  ASSERT_EQUAL(joe->lead_card(trump), nine_clubs);

  delete joe;
}

TEST(test_play_card_example_1) {
    // Setting up player with specific cards
    Player *sydney = Player_factory("Sydney", "Simple");
    sydney->add_card(Card(NINE, CLUBS));
    sydney->add_card(Card(TEN, CLUBS));
    sydney->add_card(Card(JACK, CLUBS));
    sydney->add_card(Card(QUEEN, SPADES));
    sydney->add_card(Card(KING, SPADES));

    // Playing a card with specific conditions
    Card card_played = sydney->play_card(Card(JACK, SPADES), HEARTS);

    // Asserting the played card matches the expected result
    ASSERT_EQUAL(Card(KING, SPADES), card_played);

    // Cleanup
    delete sydney;
}

TEST(test_play_card_example_2) {
    // Setting up player with specific cards
    Player *sydney = Player_factory("Sydney", "Simple");
    sydney->add_card(Card(ACE, CLUBS));
    sydney->add_card(Card(TEN, DIAMONDS));
    sydney->add_card(Card(JACK, HEARTS));
    sydney->add_card(Card(QUEEN, HEARTS));

    // Playing a card with specific conditions
    Card card_played = sydney->play_card(Card(KING, CLUBS), HEARTS);

    // Asserting the played card matches the expected result
    ASSERT_EQUAL(Card(ACE, CLUBS), card_played);

    // Cleanup
    delete sydney;
}

TEST(test_play_card_example_3) {
    // Setting up player with specific cards
    Player *alice = Player_factory("Sydney", "Simple");
    alice->add_card(Card(NINE, CLUBS));

    // Playing a card with specific conditions
    Card card_played = alice->play_card(Card(KING, CLUBS), HEARTS);

    // Asserting the played card matches the expected result
    ASSERT_EQUAL(Card(NINE, CLUBS), card_played);

    // Cleanup
    delete alice;
}

TEST(test_add_and_discard) {
    // Arrange
    Player *kate = Player_factory("Rachel", "Simple");
    Card nineHearts(NINE, HEARTS);
    Card tenHearts(TEN, HEARTS);
    Card kingHearts(KING, HEARTS);
    Card aceHearts(ACE, HEARTS);
    Card aceClubs(ACE, CLUBS);

    // Act
    kate->add_card(nineHearts);
    kate->add_card(tenHearts);
    kate->add_card(kingHearts);
    kate->add_card(aceHearts);
    kate->add_card(aceClubs);
    kate->add_and_discard(aceClubs);

    // Cleanup
    delete kate;
}



TEST_MAIN()
