//
// Created by Ivan Ramyk on 10/16/19.
//
#include <gtest/gtest.h>
#include "../src/dice.h"

TEST(TestDice, DiceRandomInit){
    for (int i = 0; i < 20; ++i) {
        Dice random_dice(true);
        EXPECT_TRUE(random_dice.is_valid());// check random init
    }
}

TEST(TestDice, DiceAdd){
    Dice dice;
    dice.add(0.5);
    dice.add(0.3);
    dice.add(0.2);// custom dice
    EXPECT_TRUE(dice.is_valid());// sum probabilities 1
}

TEST(TestSetDices, DiceSetInit){

}