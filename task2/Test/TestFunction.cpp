//
// Created by Ivan Ramyk on 10/28/19.
//

#include <gtest/gtest.h>

#include "../Headers/Translate.h"
#include "../Headers/Function.h"


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


TEST(TestFunction, TestIntegerFunction){
    Function function;
    EXPECT_TRUE(function.calculate(5) == "twenty-five");
    EXPECT_TRUE(function.calculate(11) == "eleven");
    EXPECT_TRUE(function.calculate(-1) == "two hundred and eight");
    EXPECT_TRUE(function.calculate(-2) == "one hundred and seventy");
}

TEST(TestFunction, TestDoubleFunction){
    Function function;
    EXPECT_TRUE(function.calculate(0.2) == "zero point nine five");
    EXPECT_TRUE(function.calculate(0.1) == "zero point nine one");
    EXPECT_TRUE(function.calculate(10.2) == "zero point zero four");
}

TEST(TestFunction, TestTextFunction){
    Function function;
    std::string s = "a ab abc";
    EXPECT_TRUE(function.calculate(s) == "abc ab a");
    s = "gg temp cut";
    EXPECT_TRUE(function.calculate(s) == "cut temp gg");
    s = "d";
    EXPECT_TRUE(function.calculate(s) == "d");
}

TEST(TestFunction, TestPairFunction){
    Function function;
    std::string s = "a ab abc";
    int a = 11;
    std::pair<std::string, int> p = {s, a};
    //std::cout << function.calculate(p) << "\n";
    EXPECT_TRUE(function.calculate(p) == "eleven abc ab a");
}

TEST(TestFunction, TestVectorFunction){
    Function function;
    std::vector <double> p = {0.1, 0.1, 0.2, 0.2, 10.1};
    //std::cout << function.calculate(p) << "\n";
    EXPECT_TRUE(function.calculate(p) == "zero point nine five zero point nine one zero point zero two");
}

TEST(TestFunction, TestErrorFunction){
    Function function;
    char p = 'u';
    EXPECT_TRUE(function.calculate(p) == "sorry please try again");
}



