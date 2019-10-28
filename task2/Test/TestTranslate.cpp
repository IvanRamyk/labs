//
// Created by Ivan Ramyk on 10/28/19.
//

#include "../Headers/Translate.h"

#include <gtest/gtest.h>
#include <iostream>

TEST(TestTranslation, TestIntegerUnderTen){
    Translate<int> translate;
    EXPECT_TRUE(translate.translate(0) == "zero");
    EXPECT_TRUE(translate.translate(1) == "one");
    EXPECT_TRUE(translate.translate(2) == "two");
    EXPECT_TRUE(translate.translate(3) == "three");
    EXPECT_TRUE(translate.translate(4) == "four");
    EXPECT_TRUE(translate.translate(5) == "five");
    EXPECT_TRUE(translate.translate(6) == "six");
    EXPECT_TRUE(translate.translate(7) == "seven");
    EXPECT_TRUE(translate.translate(8) == "eight");
    EXPECT_TRUE(translate.translate(9) == "nine");
}

TEST(TestTranslation, TestInteger10_19){
    Translate<int> translate;
    EXPECT_TRUE(translate.translate(10) == "ten");
    EXPECT_TRUE(translate.translate(11) == "eleven");
    EXPECT_TRUE(translate.translate(12) == "twelve");
    EXPECT_TRUE(translate.translate(13) == "thirteen");
    EXPECT_TRUE(translate.translate(14) == "fourteen");
    EXPECT_TRUE(translate.translate(15) == "fifteen");
    EXPECT_TRUE(translate.translate(16) == "sixteen");
    EXPECT_TRUE(translate.translate(17) == "seventeen");
    EXPECT_TRUE(translate.translate(18) == "eighteen");
    EXPECT_TRUE(translate.translate(19) == "nineteen");
}

TEST(TestTranslation, TestInteger20_99){
    Translate<int> translate;
    EXPECT_TRUE(translate.translate(20) == "twenty");
    EXPECT_TRUE(translate.translate(30) == "thirty");
    EXPECT_TRUE(translate.translate(42) == "forty-two");
    EXPECT_TRUE(translate.translate(51) == "fifty-one");
    EXPECT_TRUE(translate.translate(99) == "ninety-nine");
}

TEST(TestTranslation, TestIntegerOver100){
    Translate<int> translate;
    EXPECT_TRUE(translate.translate(200) == "two hundred");
    EXPECT_TRUE(translate.translate(210) == "two hundred and ten");
    EXPECT_TRUE(translate.translate(313) == "three hundred thirteen");
    EXPECT_TRUE(translate.translate(142) == "one hundred and forty-two");
    EXPECT_TRUE(translate.translate(499) == "four hundred and ninety-nine");
}

TEST(TestTranslation, TestDoubles){
    Translate<double> translate;
    EXPECT_TRUE(translate.translate(0.2) == "zero point two");
    std::cout << translate.translate(123.23) << "\n";
    EXPECT_TRUE(translate.translate(123.23) == "one hundred and twenty-three point two three");
    EXPECT_TRUE(translate.translate(313) == "three hundred thirteen");
    EXPECT_TRUE(translate.translate(142.03) == "one hundred and forty-two point zero three");
    EXPECT_TRUE(translate.translate(499) == "four hundred and ninety-nine");
}

TEST(TestTranslation, TestError){
    Translate<std::string> translate;
    EXPECT_TRUE(translate.translate("abs") == "sorry please try again");
}
