//
// Created by Ivan Ramyk on 10/29/19.
//

#include "../Headers/Global.h"
#include "../Headers/Alpha.h"
#include "../Headers/Beta.h"
#include "../Headers/Gamma.h"
#include "../Headers/Delta.h"

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