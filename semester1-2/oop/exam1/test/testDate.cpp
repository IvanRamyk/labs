//
// Created by ivan on 15.12.19.
//
#include <gtest/gtest.h>
#include "../date.h"


TEST(TestDate, TestTransform){
    Date date(1);
    EXPECT_EQ(date.day, 2);
    EXPECT_EQ(date.month, 1);
    EXPECT_EQ(date.year, 0);
    Date date2(365);
    EXPECT_TRUE(date2.day == 1);
    EXPECT_TRUE(date2.month == 1);
    EXPECT_TRUE(date2.year == 1);
    Date date3(31);
    EXPECT_EQ(date3.day, 1);
    EXPECT_EQ(date3.month, 2);
    EXPECT_EQ(date3.year, 0);
}

TEST(TestDate, TestAdd){
    Date date(1);
    Date start(2019, 12, 31);
    start = start + date;
    EXPECT_EQ(start.day, 1);
    EXPECT_EQ(start.month, 1);
    EXPECT_EQ(start.year, 2020);
}

TEST(TestDate, TestDif){
    Date start(2019, 12, 31);
    start = start - 1;
    EXPECT_EQ(start.day, 30);
    EXPECT_EQ(start.month, 12);
    EXPECT_EQ(start.year, 2019);
}