//
// Created by Ivan Ramyk on 3/21/20.
//

#include <gtest/gtest.h>
#include <memory>
#include "../BPlusTree.hpp"

using std::shared_ptr;
using std::make_shared;

TEST(SearchingInBtree, algorithms) {
    shared_ptr<BPlusTree<int>> tree = make_shared<BPlusTree<int>>(5);
    for (int i = 0; i < 100; ++i) {
        tree->insert(i, make_shared<int>(i));
    }

    for (int i = 0; i < 10; ++i) {
        int searched{rand() % 100};
        EXPECT_TRUE(*tree->search(searched) == searched);
    }

    for (int i = 0; i < 5; ++i) {
        EXPECT_TRUE(tree->search(rand() + 100) == nullptr);
    }
}

TEST(InsertionInBtree, algorithms)  {
    shared_ptr<BPlusTree<int>> tree = make_shared<BPlusTree<int> >(4);
    for (int i = 0; i < 100; ++i) {
        tree->insert(i, make_shared<int>(i));
    }
    for (int i = 0; i < 5; ++i) {
        EXPECT_TRUE(tree->search(rand() % 100) != nullptr);
    }
}

TEST(Removing, algorithms) {
    shared_ptr<BPlusTree<int>> tree = make_shared<BPlusTree<int> >(5);
    for (int i = 0; i < 199; ++i) {
        tree->insert(i, make_shared<int>(i));
    }
    for (int i = 0; i < 10; ++i) {
        int removing = rand() % 199;
        tree->remove(removing);
        EXPECT_TRUE(tree->search(removing) == nullptr);
    }
}

TEST(General, algorithms) {
    shared_ptr<BPlusTree<int>> tree = make_shared<BPlusTree<int>>(13);
    for (int i = 0; i < 1000; ++i) {
        int element = rand() % 15000;
        tree->insert(element, make_shared<int>(element));
    }
    for (int i = 0; i < 500; ++i) {
        int element = rand() % 15000;
        tree->remove(element);
        EXPECT_TRUE(tree->search(element) == nullptr);
        tree->insert(element, make_shared<int>(element));
        EXPECT_TRUE(tree->search(element) != nullptr);
    }
}

TEST(Iterators, algorithms) {
    BPlusTree<int> tree(13);
    for (auto i = 0; i < 100; ++i) {
        tree.insert(i, make_shared<int>(i));
    }
    int counter{0};
    auto it = tree.begin();
    for(; it != tree.end(); ++it){
        EXPECT_TRUE(*it == counter);
        ++counter;
    }
}