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
    ASSERT(c3 > c1);
    ASSERT(c1 < c3);

}

TEST(test_card_properties) {
    // Test card properties and functions
    Card c1(JACK, HEARTS);
    Card c2(ACE, SPADES);

    // Trump-related functions
    ASSERT_TRUE(c1.is_left_bower(SPADES));
    ASSERT_TRUE(c2.is_trump(SPADES));

}

TEST_MAIN()
