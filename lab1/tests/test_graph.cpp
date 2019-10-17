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
    graph.add_edge(v1, v2, edge);
    graph.add_edge("Lviv", "Irpen", 13);
    graph.add_edge("Kyiv", "Irpen", 12);
}