#include "Card.hpp"
#include "unit_test_framework.hpp"
#include <iostream>

using namespace std;


TEST(test_card_ctor) {
    Card c1(ACE, HEARTS);
    ASSERT_EQUAL(ACE, c1.get_rank());
    ASSERT_EQUAL(HEARTS, c1.get_suit());
    
    Card c2(TWO, SPADES);
    ASSERT_EQUAL(TWO, c2.get_rank());
    ASSERT_EQUAL(SPADES, c2.get_suit());

    Card c3(KING, CLUBS);
    ASSERT_EQUAL(KING, c3.get_rank());
    ASSERT_EQUAL(CLUBS, c3.get_suit());

    // Test constructing cards with face cards and aces
    Card c4(JACK, HEARTS);
    ASSERT_EQUAL(JACK, c4.get_rank());
    ASSERT_EQUAL(HEARTS, c4.get_suit());

    Card c5(ACE, DIAMONDS);
    ASSERT_EQUAL(ACE, c5.get_rank());
    ASSERT_EQUAL(DIAMONDS, c5.get_suit());

}

TEST(test_card_comparison) {
    // Test comparison operators
    Card c1(TWO, SPADES);
    Card c2(TWO, SPADES);
    Card c3(KING, CLUBS);

    // Equality
    ASSERT_EQUAL(c1, c2);

    // Inequality
    ASSERT_NOT_EQUAL(c1, c3);
    //ASSERT(c3 > c1);
   //ASSERT(c1 < c3);

}

TEST(test_card_properties) {
    // Test card properties and functions
    Card c1(JACK, HEARTS);
    Card c2(ACE, SPADES);
    Card c3(JACK, CLUBS);  

    // Trump-related functions
    ASSERT_FALSE(c1.is_left_bower(SPADES));
    ASSERT_FALSE(c2.is_left_bower(SPADES));  // Ace is not a left bower
    ASSERT_TRUE(c2.is_trump(SPADES));  // Ace is a trump card
    ASSERT_FALSE(c1.is_trump(SPADES));  // Jack of Hearts is not a trump card
    ASSERT_FALSE(c3.is_left_bower(CLUBS));  // Jack of Clubs is a left bower for CLUBS
    ASSERT_TRUE(c3.is_trump(CLUBS));  // Jack of Clubs is a trump card for CLUBS
    ASSERT_TRUE(c3.is_left_bower(SPADES));  // Jack of Clubs is not a left bower for SPADES
    ASSERT_TRUE(c3.is_trump(SPADES));  // Jack of Clubs is not a trump card for SPADES
}

TEST(test_suit_input) {
    Suit s;

    // Test valid input
    istringstream validInput("Hearts");
    validInput >> s;
    ASSERT_EQUAL(HEARTS, s);
}

TEST(test_operator_input) {
    std::istringstream input_stream("Jack of Hearts");
    Card c;
    input_stream >> c;

    ASSERT_EQUAL(JACK, c.get_rank());
    ASSERT_EQUAL(HEARTS, c.get_suit());
}

TEST(test_is_trump) {
    // Trump suit is SPADES
    Card c1(JACK, SPADES);  // Left bower
    Card c2(TEN, SPADES);   // Trump card
    Card c3(QUEEN, HEARTS); // Not a trump card

    // Check for left bower
    ASSERT_TRUE(c1.is_trump(SPADES));

    // Check for a regular trump card
    ASSERT_TRUE(c2.is_trump(SPADES));

    // Check for non-trump card
    ASSERT_FALSE(c3.is_trump(SPADES));

    // Trump suit is HEARTS
    Card c4(JACK, CLUBS);    // Not a trump card
    Card c5(ACE, HEARTS);    // Trump card
    Card c6(KING, HEARTS);   // Trump card

    // Check for non-trump card
    ASSERT_FALSE(c4.is_trump(HEARTS));

    // Check for regular trump cards
    ASSERT_TRUE(c5.is_trump(HEARTS));
    ASSERT_TRUE(c6.is_trump(HEARTS));
}
TEST(test_card_less_trump) {
    // Trump suit is SPADES
    Card trumpCard(JACK, SPADES);
    Card nonTrumpCard(ACE, HEARTS);
    Card ledCard(TWO, DIAMONDS);

    // Trump card is always considered less than a non-trump card
    ASSERT_TRUE(Card_less(trumpCard, nonTrumpCard, ledCard, SPADES));
    ASSERT_FALSE(Card_less(nonTrumpCard, trumpCard, ledCard, SPADES));
}

TEST(test_card_less_same_suit) {
    // Trump suit is HEARTS
    Card card1(TEN, HEARTS);
    Card card2(QUEEN, HEARTS);
    Card ledCard(FOUR, HEARTS);

    // Both cards have the same suit, compare based on rank
    ASSERT_TRUE(Card_less(card1, card2, ledCard, HEARTS));
    ASSERT_FALSE(Card_less(card2, card1, ledCard, HEARTS));
}

TEST(test_card_less) {
    // Trump suit is CLUBS
    Card card1(JACK, DIAMONDS);
    Card card2(TEN, SPADES);
    Card ledCard(ACE, CLUBS);

    // Trump card vs non-trump card, non-trump card should be considered lower
    Card card3(JACK, CLUBS);
    Card card4(TEN, SPADES);
    Card ledCard2(ACE, CLUBS);
    ASSERT_TRUE(Card_less(card3, card4, ledCard2, CLUBS));

    // Trump card vs non-trump card, trump card should be considered higher
    Card card5(JACK, CLUBS);
    Card card6(TEN, SPADES);
    Card ledCard3(ACE, SPADES);
    ASSERT_FALSE(Card_less(card5, card6, ledCard3, SPADES));

    // Same suit, same rank, should return false
    Card card9(ACE, SPADES);
    Card card10(ACE, SPADES);
    Card ledCard5(JACK, SPADES);
    ASSERT_FALSE(Card_less(card9, card10, ledCard5, SPADES));
}

TEST_MAIN()
