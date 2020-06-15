//
// Created by ivan on 08.04.20.
//

#include <gtest/gtest.h>
#include "../src/SplayTree.hpp"
#include "../src/Tree.hpp"
#include <cmath>
#include <set>

TEST(SplayTree, CreationSearcing){
    //RedBlackTreeNode<int> * node;
    SplayTree<int> tree;
    tree.insert(3);
    tree.insert(5);
    auto v = tree.print();

    EXPECT_TRUE(tree.search(3) != nullptr);
    EXPECT_EQ(tree.search(3)->value(), 3);
    tree.insert(2);
    tree.insert(17);
    EXPECT_TRUE(tree.search(11) == nullptr);
    EXPECT_EQ(tree.search(2)->value(), 2);
    EXPECT_EQ(tree.search(17)->value(), 17);
}

TEST(SplayTree, Remove){
    SplayTree<int> tree;
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
    EXPECT_TRUE(tree.search(0) != nullptr);
    EXPECT_TRUE(tree.search(1) != nullptr);
    EXPECT_TRUE(tree.search(2) != nullptr);
    EXPECT_TRUE(tree.search(3) != nullptr);
    for (int i = 0; i < 4; ++i){
        EXPECT_TRUE(tree.search(i) != nullptr);
    }
    for (int i = 4; i < 14; ++i)
        EXPECT_EQ(tree.search(i), nullptr);
    for (int i = 14; i < 20; ++i){
        EXPECT_TRUE(tree.search(i) != nullptr);
    }
}

TEST(SplayTree, CompareWithSTL){
    SplayTree<int> tree;
    std::set <int> s;
    for (int i = 0; i < 10000; ++i){
        int value = rand() % 10000;
        if (!s.count(value)) {
            tree.insert(value);
            s.insert(value);
        }
    }
    for (auto it = s.begin(); it != s.end(); ++it)
        EXPECT_TRUE(tree.search(*it) != nullptr);

    int total = 0;
    for (int i = 0; i < 10000; ++i){
        int value = rand() % 10000;
        if (s.count(value) != 0)
            total++;
        if (s.count(value)) {
            tree.remove(tree.search(value));
            s.erase(value);
        }
    }
    for (auto it = s.begin(); it != s.end(); ++it)
        EXPECT_TRUE(tree.search(*it) != nullptr);
}

TEST(SplayTree, Iterator){
    std::vector <int> v;
    SplayTree<int> tree;
    for (int i = 0; i < 100; ++i) {
        tree.insert(2 * i);
        v.push_back(2 * i);
    }
    int k = 0;
    for (auto it = tree.begin(); it!= tree.end(); ++it, ++k){
        EXPECT_EQ(*it, v[k]);
    }

}