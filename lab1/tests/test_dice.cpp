//
// Created by Ivan Ramyk on 10/16/19.
//
#include <gtest/gtest.h>
#include "../src/dice.h"

using std::vector;

TEST(TestDice, DiceRandomInit){
    for (int i = 0; i < 20; ++i) {
        Dice random_dice(true);
        EXPECT_TRUE(random_dice.is_valid());// check random init
    }
}

TEST(TestDice, DiceVectorInit){
    vector <double> prob;
    prob.push_back(0.3);
    prob.push_back(0.1);
    prob.push_back(0.2);
    prob.push_back(0.3);
    prob.push_back(0.1);
    Dice vector_dice(prob);
    for (int i = 0; i < 5; ++i)
        EXPECT_DOUBLE_EQ(prob[i], vector_dice.get_side(i));
}

TEST(TestDice, DiceAdd){
    Dice dice;
    dice.add(0.5);
    dice.add(0.3);
    dice.add(0.2);// custom dice
    EXPECT_TRUE(dice.is_valid());// sum probabilities 1
}

TEST(TestSetDices, SetDicesExpectedSum){// testing operator <
    SetDices set;
    set.add(Dice({0.5, 0.5}));
    set.add(Dice({0.5, 0.5}));
    set.add(Dice({0.5, 0.5}));
    set.add(Dice({0.5, 0.5}));
    EXPECT_DOUBLE_EQ(6, set.expected_sum());
    SetDices set_low;
    set_low.add(Dice({0.6, 0.4}));
    set_low.add(Dice({0.6, 0.4}));
    set_low.add(Dice({0.6, 0.4}));
    set_low.add(Dice({0.6, 0.4}));
    EXPECT_TRUE(set_low < set);// expected sum for set_low < expected sum for set
}

TEST(TestSetDices, SetDicesAllSums){// testing operator <
    SetDices set;
    set.add(Dice({0.5, 0.5}));
    set.add(Dice({0.5, 0.5}));
    set.add(Dice({0.5, 0.5}));
    set.add(Dice({0.5, 0.5}));
    set.add(Dice({0, 1, 0, 0}));
    vector <std::pair<int, double>> sum_prob = set.probability_for_each_sum();
    for (int i = 0; i < sum_prob.size(); ++i)
        switch (sum_prob[i].first){
            case 6:
            {
                EXPECT_DOUBLE_EQ(0.0625, sum_prob[i].second);
                break;
            }
            case 7:
            {
                EXPECT_DOUBLE_EQ(0.25, sum_prob[i].second);
                break;
            }
            case 8:
            {
                EXPECT_DOUBLE_EQ(0.375, sum_prob[i].second);
                break;
            }
            case 9:
            {
                EXPECT_DOUBLE_EQ(0.25, sum_prob[i].second);
                break;
            }
            case 10:
            {
                EXPECT_DOUBLE_EQ(0.0625, sum_prob[i].second);
                break;
            }
            default:
                break;
        }

}

TEST(TestSetDices, SetDicesAdd){
    SetDices set;
    EXPECT_TRUE(set.add(Dice({0.5, 0.3, 0.2})));
    EXPECT_TRUE(!set.add(Dice({0.5, 0.3})));// we can't add dice with sum of prob != 1
}