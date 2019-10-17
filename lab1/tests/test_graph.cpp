//
// Created by Ivan Ramyk on 10/16/19.
//

#include <gtest/gtest.h>
#include "../src/graph.h"

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

TEST(TestGraphStandartTypes, TestGraphSpanningTree){
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