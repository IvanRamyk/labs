//
// Created by Ivan Ramyk on 10/16/19.
//

#include <gtest/gtest.h>
#include "../src/graph.h"
#include "../src/dice.h"

TEST(TestGraphStandartTypes, TestGraphInit){
    Graph<std::string, int> graph;
    std::string v1 = "Kyiv";
    std::string v2 = "Lviv";
    int edge = 145;
    graph.addVertex("Kyiv");
    graph.addVertex("Lviv");
    graph.addVertex("Irpen");
    EXPECT_TRUE(graph.addEdge(v1, v2, edge));
    EXPECT_TRUE(graph.addEdge("Lviv", "Irpen", 13));
    EXPECT_TRUE(graph.addEdge("Kyiv", "Irpen", 12));
    EXPECT_TRUE(!graph.addEdge("Kyiv", "abc", 1));// we can't add this edge because no vertex "abc"
}

TEST(TestGraphStandartTypes, TestGraphComponents){
    Graph<std::string, int> graph;
    std::string v1 = "Kyiv";
    std::string v2 = "Lviv";
    int edge = 145;
    graph.addVertex("Kyiv");
    graph.addVertex("Lviv");
    graph.addVertex("Irpen");
    graph.addVertex("Kirov");
    graph.addEdge(v1, v2, edge);
    graph.addEdge("Lviv", "Irpen", 13);
    graph.addEdge("Kyiv", "Irpen", 12);
    vector <vector <std::string>> components = graph.searchComponent();
    EXPECT_EQ(2, components.size());
    EXPECT_EQ(components[0][0], "Kyiv");
    EXPECT_EQ(components[0][1], "Lviv");
    EXPECT_EQ(components[0][2], "Irpen");
    EXPECT_EQ(components[1][0], "Kirov");
}

TEST(TestTreeStandartTypes, TestGraphSpanningTree){
    Graph<std::string, int> graph;
    std::string v1 = "Kyiv";
    std::string v2 = "Lviv";
    int edge = 145;
    graph.addVertex("Kyiv");
    graph.addVertex("Lviv");
    graph.addVertex("Irpen");
    EXPECT_TRUE(graph.addEdge(v1, v2, edge));
    EXPECT_TRUE(graph.addEdge("Lviv", "Irpen", 13));
    EXPECT_TRUE(graph.addEdge("Kyiv", "Irpen", 12));
    Graph<std::string, int> g_tree = graph.minimumSpanningTree();
    EXPECT_EQ(g_tree.center(), 2);
    Tree<std::string, int> tree;
    tree.convert(g_tree, g_tree.center());
    EXPECT_TRUE(tree.totalWeight() == 25);
}

TEST(TestGraphCustomTypes, TestGraphInit){
    Graph<Dice, SetDices> graph;
    Dice v1 = Dice({0.3, 0.3, 0.3, 0.1});
    Dice v2 = Dice({0.3, 0.2, 0.4, 0.05, 0.05});
    Dice v3 = Dice({0.5, 0,5});
    SetDices edge1(true, 2);
    SetDices edge2(true, 2);
    SetDices edge3(true, 12);
    graph.addVertex(v1);
    graph.addVertex(v2);
    graph.addVertex(v3);
    EXPECT_TRUE(graph.addEdge(v1, v2, edge1));
    EXPECT_TRUE(graph.addEdge(v2, v3, edge2));
    EXPECT_TRUE(graph.addEdge(v1, v3, edge3));
    EXPECT_TRUE(!graph.addEdge(v3, Dice(true), SetDices(true)));// we can't add this edge because no second vertex
}

TEST(TestGraphCustomTypes, TestGraphComponents){
    Graph<Dice, SetDices> graph;
    Dice v1 = Dice({0.3, 0.3, 0.3, 0.1});
    Dice v2 = Dice({0.3, 0.2, 0.4, 0.05, 0.05});
    Dice v3 = Dice({0.5, 0,5});
    SetDices edge1(true, 2);
    SetDices edge2(true, 2);
    SetDices edge3(true, 12);
    graph.addVertex(v1);
    graph.addVertex(v2);
    graph.addVertex(v3);
    graph.addVertex(Dice(true));
    graph.addVertex(Dice(true));
    graph.addEdge(v1, v2, edge1);
    graph.addEdge(v2, v3, edge2);
    graph.addEdge(v1, v3, edge3);
    vector <vector <Dice>> components = graph.searchComponent();
    EXPECT_EQ(3, components.size());
    EXPECT_TRUE(components[0][0] == v1);
    EXPECT_TRUE(components[0][1] == v2);
    EXPECT_TRUE(components[0][2] == v3);
}

TEST(TestTreeCustomTypes, TestGraphSpanningTree){
    Graph<Dice, SetDices> graph;
    Dice v1 = Dice({0.3, 0.3, 0.3, 0.1});
    Dice v2 = Dice({0.3, 0.2, 0.4, 0.05, 0.05});
    Dice v3 = Dice({0.5, 0,5});
    SetDices edge1(true, 2);
    SetDices edge2(true, 2);
    SetDices edge3(true, 12);
    graph.addVertex(v1);
    graph.addVertex(v2);
    graph.addVertex(v3);
    graph.addEdge(v1, v2, edge1);
    graph.addEdge(v2, v3, edge2);
    graph.addEdge(v1, v3, edge3);
    Graph<Dice, SetDices> g_tree = graph.minimumSpanningTree();
    Tree<Dice, SetDices> tree;
    tree.convert(g_tree, 0);
    EXPECT_TRUE(tree.totalWeight() == edge1 + edge2);
}
