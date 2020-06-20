//
// Created by Ivan Ramyk on 10/29/19.
//

#include "../Headers/Global.h"
#include "../Headers/Alpha.h"
#include "../Headers/Beta.h"
#include "../Headers/Gamma.h"
#include "../Headers/Delta.h"
#include "../Headers/Function.h"

#include <gtest/gtest.h>


TEST(TestDestructor, TestAlpha){
    S = 0;
    {
        Alpha class1;
        Alpha class2;
    }
    EXPECT_EQ(S, 25);
}

TEST(TestDestructor, TestBeta){
    S = 0;
    {
        Beta class1;
        Beta class2;
    }
    EXPECT_EQ(S, -15);
}

TEST(TestDestructor, TestGamma){
    S = 0;
    {
        Gamma class1;
        Gamma class2;
    }
    EXPECT_EQ(S, -3);
}

TEST(TestDestructor, TestDelta){
    S = 0;
    {
        Delta class1;
        Delta class2;
    }
    //std::cout << -9 / 2;
    EXPECT_EQ(S, -5);
}

TEST(TestPrediction, TestPredictionCase1){
    int predict = 0;
    {
        Alpha c1, c2, c3, c4, c5, c6;
        Beta b1;
        Beta b2;
        Beta b3;
        Beta b4;
        Alpha a1;
        Gamma g1, g2, g3;
        Delta d1, d2;
        Function f;
        f.addClass(d2);
        f.addClass(d1);
        f.addClass(g3);
        f.addClass(g2);
        f.addClass(g1);
        f.addClass(a1);
        f.addClass(b4);
        f.addClass(b3);
        f.addClass(b2);
        f.addClass(b1);
        f.addClass(c6);
        f.addClass(c5);
        f.addClass(c4);
        f.addClass(c3);
        f.addClass(c2);
        f.addClass(c1);
        predict = f.predict();
    }
    EXPECT_EQ(predict, S);
}