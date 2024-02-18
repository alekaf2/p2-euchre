#include "Pack.hpp"
#include "unit_test_framework.hpp"

#include <iostream>

using namespace std;

TEST(test_pack_default_ctor) {
    Pack pack;
    Card first = pack.deal_one();
    ASSERT_EQUAL(NINE, first.get_rank());
    ASSERT_EQUAL(SPADES, first.get_suit());
}

TEST(test_pack_deal_multiple_cards) {
    Pack pack;
    Card first = pack.deal_one();
    Card second = pack.deal_one();
    Card third = pack.deal_one();

    ASSERT_EQUAL(NINE, first.get_rank());
    ASSERT_EQUAL(SPADES, first.get_suit());
    ASSERT_EQUAL(TEN, second.get_rank());
    ASSERT_EQUAL(SPADES, second.get_suit());
    ASSERT_EQUAL(JACK, third.get_rank());
    ASSERT_EQUAL(SPADES, third.get_suit());
}

TEST(test_pack_reset) {
    Pack pack;
    Card first = pack.deal_one();
    pack.reset();
    Card afterReset = pack.deal_one();

    ASSERT_EQUAL(NINE, first.get_rank());
    ASSERT_EQUAL(SPADES, first.get_suit());
    ASSERT_EQUAL(TEN, afterReset.get_rank());
    ASSERT_EQUAL(SPADES, afterReset.get_suit());
}

TEST(test_pack_shuffle) {
    Pack pack;
    Card beforeShuffle = pack.deal_one();
    pack.shuffle();
    Card afterShuffle = pack.deal_one();

    ASSERT_EQUAL(NINE, beforeShuffle.get_rank());
    ASSERT_EQUAL(SPADES, beforeShuffle.get_suit());
    ASSERT_NOT_EQUAL(beforeShuffle, afterShuffle);
}

TEST_MAIN()
