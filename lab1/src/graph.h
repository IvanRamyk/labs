//
// Created by Ivan Ramyk on 10/10/19.
//
#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <iostream>
#include <queue>
#include <algorithm>

using std::vector;
using std::cout;
using std::cin;
using std::queue;
using std::pair;

template<typename EdgeT>
struct Edge {
    EdgeT data;
    int to;

    Edge() = default;

    Edge(EdgeT _data, int _to) {
        data = _data;
        to = _to;
    }
};

template<typename EdgeT>
struct SpanningTreeEdge {
    EdgeT data;
    int from;
    int to;

    SpanningTreeEdge() = default;

    SpanningTreeEdge(EdgeT Data, int _from, int _to) {
        data = Data;
        to = _to;
        from = _from;
    }

    bool operator <(SpanningTreeEdge another){
        return this->data < another.data;
    }
};

struct DisjointSet {
    vector<int> parent;

    DisjointSet(int n = 0){
        parent.resize(n);
        for (int i = 0; i < n; ++i)
            parent[i] = - 1;
    }

    int find_root(int v) {
        if (parent[v] == -1) return v;
        return parent[v] = find_root(parent[v]);
    }

    void join(int u, int v) {
        u = find_root(u), v = find_root(v);
        if (u != v)
            parent[u] = v;
    }

    bool same_set(int u, int v) {
        return find_root(u) == find_root(v);
    }
};

template <typename VertexT, typename EdgeT>
class Tree;

template <typename VertexT, typename EdgeT>
class Graph;

template<typename VertexT, typename EdgeT>
class Graph {
    friend class Tree<VertexT, EdgeT>;

private:
    vector <vector<Edge<EdgeT>>> adj;
    vector <VertexT> vertexes;
    int number_vertex;
    bool directed;

    int position(VertexT v);

    void dfs(int v, std::vector <bool> &used, std::vector <VertexT> &component);

    bool top_dfs (int v, std::vector <int>& used, std::vector <VertexT> &ans);

public:
    Graph(bool is_directed = false);

    void add_vertex(VertexT v);

    bool add_edge(VertexT from, VertexT to, EdgeT edge);

    vector < std::vector <VertexT> > search_component();

    vector <pair<int, VertexT>> bfs(VertexT V);

    int bfs(VertexT V1, VertexT V2);

    Graph<VertexT, EdgeT> minimum_spanning_tree();

    std::pair<bool, vector <VertexT>> topological_sort();

    void print();

    int center();
};

template <typename  VertexT, typename  EdgeT>
struct TreeNode{
    VertexT data;
    EdgeT edge;
    vector<TreeNode<VertexT, EdgeT> *> children;
    TreeNode() = default;
    TreeNode(VertexT _data, EdgeT _edge){
        data = _data;
        edge = _edge;
    }
};

template <typename VertexT, typename EdgeT>
class Tree{
    //friend class Graph<VertexT, EdgeT>;

private:
    TreeNode<VertexT, EdgeT> * root;

    TreeNode<VertexT, EdgeT> * dfs(Graph<VertexT, EdgeT> &graph, vector<bool> &used, int v, EdgeT edge = EdgeT());

    EdgeT total(TreeNode<VertexT, EdgeT> * current_node);

    void print_node(TreeNode<VertexT, EdgeT> * current_node);
public:
    Tree();

    void convert(Graph<VertexT, EdgeT> graph, int root);

    void print();

    EdgeT total_w();
};

#include "graph.hxx"

#endif //GRAPH_H
