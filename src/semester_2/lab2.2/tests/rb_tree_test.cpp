//
// Created by Ivan Ramyk on 3/21/20.
//

#include <gtest/gtest.h>
#include "../src/RedBlackTree.hpp"
#include <cmath>
#include <set>
#include <random>
#include <utility>

TEST(RBTree, CreationSearcing){
    //RedBlackTreeNode<int> * node;
    RedBlackTree<int> tree;
    tree.insert(3);
    EXPECT_TRUE(tree.search(3) != nullptr);
    EXPECT_EQ(tree.search(3)->value(), 3);
    tree.insert(5);
    tree.insert(2);
    tree.insert(17);
    EXPECT_TRUE(tree.search(11) == nullptr);
    EXPECT_EQ(tree.search(2)->value(), 2);
    EXPECT_EQ(tree.search(17)->value(), 17);
}

TEST(RBTree, Height){
    RedBlackTree<int> tree;
    for (int i = 0 ; i < 1000; ++i) {
        tree.insert(i);
        EXPECT_TRUE(tree.height() <int(2 * (std::log2(i + 1) + 1)));
    }
}

TEST(RBTree, Remove){
    RedBlackTree<int> tree;
    for (int i = 0 ; i < 20; ++i) {
        tree.insert(i);
    }
    tree.remove(tree.search(4));
    tree.remove(tree.search(5));
    tree.remove(tree.search(6));
    tree.remove(tree.search(7));
    tree.remove(tree.search(8));
    tree.remove(tree.search(9));
    tree.remove(tree.search(10));
    tree.remove(tree.search(11));
    tree.remove(tree.search(12));
    tree.remove(tree.search(13));
    for (int i = 0; i < 4; ++i){
        EXPECT_TRUE(tree.search(i) != nullptr);
    }
    for (int i = 4; i < 14; ++i)
        EXPECT_EQ(tree.search(i), nullptr);
    for (int i = 14; i < 20; ++i){
        EXPECT_TRUE(tree.search(i) != nullptr);
    }
}

TEST(RBTree, select1){
    RedBlackTree<int> tree;
    for (int i = 0 ; i < 20; ++i) {
        tree.insert(i);
    }
    for (int i = 1 ; i <= 20; ++i) {
        EXPECT_TRUE(tree.select(i) != nullptr);
        EXPECT_EQ(tree.select(i)->value(), i - 1);
    }
    tree.remove(tree.search(5));
    tree.remove(tree.search(6));
    tree.remove(tree.search(7));
    tree.remove(tree.search(8));
    tree.remove(tree.search(9));
    tree.remove(tree.search(10));
    tree.remove(tree.search(11));
    tree.remove(tree.search(12));
    tree.remove(tree.search(13));
    for (int i = 6 ; i <= 11; ++i) {
        EXPECT_TRUE(tree.select(i) != nullptr);
        EXPECT_EQ(tree.select(i)->value(), i + 8);
    }
}


TEST(RBTree, select2){
    RedBlackTree<int> tree;
    for (int i = 0 ; i < 20; ++i)
        tree.insert(i);
    for (int i = 0; i < 10; ++i)
        tree.remove(tree.search(i * 2));
    for (int i = 0; i < 10; ++i)
        EXPECT_EQ(tree.select(i + 1)->value(), 2 * i + 1);
}

TEST(RBTree, order1){
    RedBlackTree<int> tree;
    for (int i = 0 ; i < 20; ++i) {
        tree.insert(i);
    }
    tree.remove(tree.search(5));
    tree.remove(tree.search(6));
    tree.remove(tree.search(7));
    tree.remove(tree.search(8));
    tree.remove(tree.search(9));
    tree.remove(tree.search(10));
    tree.remove(tree.search(11));
    tree.remove(tree.search(12));
    tree.remove(tree.search(13));
    for (int i = 6 ; i <= 11; ++i) {
        EXPECT_EQ(tree.order(tree.search(i + 8)), i);
    }
}

TEST(RBTree, order2){
    RedBlackTree<int> tree;
    for (int i = 0 ; i < 20; ++i)
        tree.insert(i);
    for (int i = 0; i < 10; ++i)
        tree.remove(tree.search(i * 2));
    for (int i = 0; i < 10; ++i)
        EXPECT_EQ(tree.order(tree.search(2 * i + 1)), i + 1);
}

TEST(RBTree, CompareWithSTL){
    srand(time(0));
    RedBlackTree<int> tree;
    std::set <int> s;
    for (int i = 0; i < 10000; ++i){
        int value = rand() % 10000000;
        if (!s.count(value)) {
            tree.insert(value);
            s.insert(value);
        }
    }
    for (auto it = s.begin(); it != s.end(); ++it){
        EXPECT_TRUE(tree.search(*it) != nullptr);
    }
}
