/*#include <iostream>
#include "dice.h"
#include "graph.h"

using std::cin;
using std::cout;

void test_dice_class(){
    SetDices dices;
    int n;
    cin >> n;
    for (int i = 0; i < n; ++i){
        Dice dice;
        int m;
        cin >> m;
        for (int j = 0; j < m; ++j){
            double temp;
            cin >> temp;
            dice.add(temp);
        }
        dices.add(dice);
    }
    vector <pair <int, double>> sums = dices.probability_for_each_sum();
    for (auto i : sums)
        cout << i.first << " " << i.second<< "\n";
    dices.print();
}

void test_graph_class(){
    Graph<std::string , int> graph;
    std::string v1 = "Kyiv";
    std::string v2 = "Lviv";
    int edge = 145;
    graph.add_vertex("Kyiv");
    graph.add_vertex("Lviv");
    graph.add_vertex("Irpen");
    graph.add_edge(v1, v2, edge);
    graph.add_edge("Lviv", "Irpen", 13);
    graph.add_edge("Kyiv", "Irpen", 12);
    Graph<std::string, int> gtree = graph.minimum_spanning_tree();
    gtree.print();
    Tree<std::string, int> tree;
    tree.convert(gtree, 0);
    tree.print();
    vector <vector<std::string>> components = graph.search_component();
    for (auto i : components) {
        for (auto j : i)
            cout << j << " ";
        cout << "\n";
    }

}

void test_random(){
    SetDices set(true);
    set.print();
}

int main() {
    //test_dice_class();
    test_graph_class();
    //test_random();
    return 0;
}*/
/*
#include <gtest/gtest.h>

TEST(DiceTests,TestName){

}*/

#include <gtest/gtest.h>
#include <gmock/gmock.h>

int main(int argc, char* argv[]){
    //std::cout << "Hello!" << "\n";
    testing::InitGoogleTest();
    RUN_ALL_TESTS();
}