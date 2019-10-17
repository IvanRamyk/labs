//
// Created by Ivan Ramyk on 10/17/19.
//

#ifndef LAB1_TEST_H
#define LAB1_TEST_H

#include <gtest/gtest.h>
#include <gmock/gmock.h>

void start_testing(){
    testing::InitGoogleTest();
    RUN_ALL_TESTS();
}

#endif //LAB1_TEST_H
