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
    graph.add_vertex("Kyiv");
    graph.add_vertex("Lviv");
    graph.add_vertex("Irpen");
    EXPECT_TRUE(graph.add_edge(v1, v2, edge));
    EXPECT_TRUE(graph.add_edge("Lviv", "Irpen", 13));
    EXPECT_TRUE(graph.add_edge("Kyiv", "Irpen", 12));
    EXPECT_TRUE(!graph.add_edge("Kyiv", "abc", 1));// we can't add this edge because no vertex "abc"
}

TEST(TestGraphStandartTypes, TestGraphComponents){
    Graph<std::string, int> graph;
    std::string v1 = "Kyiv";
    std::string v2 = "Lviv";
    int edge = 145;
    graph.add_vertex("Kyiv");
    graph.add_vertex("Lviv");
    graph.add_vertex("Irpen");
    graph.add_vertex("Kirov");
    graph.add_edge(v1, v2, edge);
    graph.add_edge("Lviv", "Irpen", 13);
    graph.add_edge("Kyiv", "Irpen", 12);
    vector <vector <std::string>> components = graph.search_component();
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
    graph.add_vertex("Kyiv");
    graph.add_vertex("Lviv");
    graph.add_vertex("Irpen");
    EXPECT_TRUE(graph.add_edge(v1, v2, edge));
    EXPECT_TRUE(graph.add_edge("Lviv", "Irpen", 13));
    EXPECT_TRUE(graph.add_edge("Kyiv", "Irpen", 12));
    Graph<std::string, int> g_tree = graph.minimum_spanning_tree();
    EXPECT_EQ(g_tree.center(), 2);
    Tree<std::string, int> tree;
    tree.convert(g_tree, g_tree.center());
    EXPECT_TRUE(tree.total_w() == 25);
}

TEST(TestGraphCustomTypes, TestGraphInit){
    Graph<Dice, SetDices> graph;
    Dice v1 = Dice({0.3, 0.3, 0.3, 0.1});
    Dice v2 = Dice({0.3, 0.2, 0.4, 0.05, 0.05});
    Dice v3 = Dice({0.5, 0,5});
    SetDices edge1(true, 2);
    SetDices edge2(true, 2);
    SetDices edge3(true, 12);
    graph.add_vertex(v1);
    graph.add_vertex(v2);
    graph.add_vertex(v3);
    EXPECT_TRUE(graph.add_edge(v1, v2, edge1));
    EXPECT_TRUE(graph.add_edge(v2, v3, edge2));
    EXPECT_TRUE(graph.add_edge(v1, v3, edge3));
    EXPECT_TRUE(!graph.add_edge(v3, Dice(true), SetDices(true)));// we can't add this edge because no second vertex
}

TEST(TestGraphCustomTypes, TestGraphComponents){
    Graph<Dice, SetDices> graph;
    Dice v1 = Dice({0.3, 0.3, 0.3, 0.1});
    Dice v2 = Dice({0.3, 0.2, 0.4, 0.05, 0.05});
    Dice v3 = Dice({0.5, 0,5});
    SetDices edge1(true, 2);
    SetDices edge2(true, 2);
    SetDices edge3(true, 12);
    graph.add_vertex(v1);
    graph.add_vertex(v2);
    graph.add_vertex(v3);
    graph.add_vertex(Dice(true));
    graph.add_vertex(Dice(true));
    graph.add_edge(v1, v2, edge1);
    graph.add_edge(v2, v3, edge2);
    graph.add_edge(v1, v3, edge3);
    vector <vector <Dice>> components = graph.search_component();
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
    graph.add_vertex(v1);
    graph.add_vertex(v2);
    graph.add_vertex(v3);
    graph.add_edge(v1, v2, edge1);
    graph.add_edge(v2, v3, edge2);
    graph.add_edge(v1, v3, edge3);
    Graph<Dice, SetDices> g_tree = graph.minimum_spanning_tree();
    Tree<Dice, SetDices> tree;
    tree.convert(g_tree, 0);
    EXPECT_TRUE(tree.total_w() == edge1 + edge2);
}
