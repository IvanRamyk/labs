#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <cmath>
#include <ctime>
#include <chrono>
#include <thread>


class graph_matrix{
private:
    std::vector <std::vector < int > > matrix;
    int number_vertex;
    int number_edge;
    bool directed;
public:
    graph_matrix(){
        number_edge = 0;
        number_vertex = 0;
        matrix.clear();
        directed = 0;
    }
    graph_matrix(int v, bool o = 0){
        directed = 0;
        number_vertex = v;
        number_edge = 0;
        matrix.resize(number_vertex);
        for (int i = 0; i < number_vertex; ++i)
            matrix[i].resize(number_vertex);
    }
    void add(int from, int to, int weight = -1){
        matrix[from][to] = weight;
        if (!directed)
            matrix[to][from] = weight;
        ++number_edge;
    }
    void graph_random(int v, int e, int o = 0){
        number_vertex = v;
        number_edge = 0;
        directed = o;
        matrix.resize(number_vertex);
        for (int i = 0; i < number_vertex; ++i)
            matrix[i].resize(number_vertex);
        for (int i = 0; i < e; ++i){
            int from = rand() % number_vertex;
            int to = rand() % number_vertex;
            if (matrix[from][to]){//edge already init
                --i;
            }
            else {
                add(from, to, 1);
            }
        }
    }
    void graph_random_weight(int v, int e, int o = 0) {
        number_vertex = v;
        directed = o;
        number_edge = 0;
        matrix.clear();
        matrix.resize(number_vertex);
        for (int i = 0; i < number_vertex; ++i)
            matrix[i].resize(number_vertex);
        for (int i = 0; i < e; ++i) {
            int from = rand() % number_vertex;
            int to = rand() % number_vertex;
            int weight = rand() % 1000;
            if (matrix[from][to]) {//edge already init
                --i;
            } else {
                add(from, to, weight);
            }
        }
    }
    void print(){
        printf("Graph with %d vertices and %d edges\nEdges:\n", number_vertex, number_edge);
        for (int i = 0; i < number_vertex; ++i){
            for (int j = 0; j < number_vertex; ++j)
                if ((directed || i < j) &&  matrix[i][j]) {
                    if (matrix[i][j] != -1) printf("(%d, %d) %d\n", i, j, matrix[i][j]);
                    else printf("(%d, %d)\n", i, j);
                }
        }
    }


    void dfs(int v, std::vector <bool> &used, std::vector <int> &component){
        used[v] = true;
        component.push_back(v);
        for (int i = 0; i < this->matrix[v].size(); ++i)
            if (this->matrix[v][i] && !used[i]) dfs(i, used, component);
    }

    std::vector < std::vector <int> > search_component(){
        std::vector <bool> used;
        used.resize(this->number_vertex);
        std::vector <std::vector <int> > result;
        std::vector <int> component;
        for (int i = 0; i < this->number_vertex; ++i)
            if (!used[i]) {
                component.clear();
                dfs(i, used, component);
                result.push_back(component);
            }
        return result;
    }

    std::vector <int> bfs(int v){
        std::vector <int> dist;
        dist.resize(this->number_vertex);
        for (int i = 0; i < this->number_vertex; ++i)
            dist[i] = -1;
        dist[v] = 0;
        std::queue <int> q;
        q.push(v);
        while (!q.empty()){
            int cur = q.front();
            q.pop();
            for (int i = 0; i < this->matrix[cur].size(); ++i)
                if (this->matrix[cur][i] && dist[i] == -1){
                    dist[i] = dist[cur] + 1;
                    q.push(i);
                }
        }
        return dist;
    }

    std::vector <int> dijkstra(int v){
        std::vector <int> dist;
        dist.resize(this->number_vertex);
        for (int i = 0; i < this->number_vertex; ++i)
            dist[i] = -1;
        dist[v] = 0;
        std::priority_queue <std::pair <int, int> > q;
        q.push({0, v});
        while (!q.empty()){
            int cur = q.top().second;
            q.pop();
            for (int i = 0; i < this->matrix[v].size(); ++i)
                if (this->matrix[cur][i] && (dist[i] == -1|| dist[i] > dist[cur] + this->matrix[cur][i])){
                    dist[i] = dist[cur] + this->matrix[cur][i];
                    q.push({-dist[i], i});
                }
        }
        return dist;
    }
    bool top_dfs (int v, std::vector <int>& used, std::vector <int> &ans) {
        used[v] = 1;
        bool answer = 1;
        for (int i = 0; i < this->matrix[v].size(); ++i)
            if (this->matrix[v][i] && !used[i])
                answer &= top_dfs(i, used, ans);
            else if (this->matrix[v][i] && used[i] == 1) return 0;
        ans.push_back(v);
        used[v] = 2;
        return answer;
    }

};

struct edge{
    int to;
    int weight;
};

class graph_adj{
private:
    std::vector <std::vector < edge > > adj;
    int number_vertex;
    int number_edge;
    bool directed;
public:
    graph_adj(){
        number_edge = 0;
        number_vertex = 0;
        adj.clear();
        directed = 0;
    }
    graph_adj(int v, bool o = 0){
        directed = o;
        number_vertex = v;
        number_edge = 0;
        adj.resize(number_vertex);
    }
    void add(int from, int to, int weight = -1){
        adj[from].push_back({to,weight});
        if (!directed)
            adj[to].push_back({from,weight});
        ++number_edge;
    }
    void graph_random(int v, int e, int o = 0){
        number_vertex = v;
        number_edge = 0;
        adj.clear();
        directed = o;
        adj.resize(number_vertex);
        for (int i = 0; i < e; ++i){
            int from = rand() % number_vertex;
            int to = rand() % number_vertex;
            add(from, to, 1);
        }
    }
    void graph_random_weight(int v, int e, int o = 0){
        number_vertex = v;
        number_edge = 0;
        adj.clear();
        directed = o;
        adj.resize(number_vertex);
        for (int i = 0; i < e; ++i){
            int from = rand() % number_vertex;
            int to = rand() % number_vertex;
            int weight = rand() % 100;
            add(from, to, weight);
        }
    }
    void print(){
        printf("Graph with %d vertices and %d edges\nEdges:\n", number_vertex, number_edge);
        for (int i = 0; i < number_vertex; ++i){
            for (auto j : adj[i])
                if (directed || i < j.to) {
                    if (j.weight != -1) printf("(%d, %d) %d\n", i, j, j.weight);
                    else printf("(%d, %d)\n", i, j);
                }
        }
    }
    void dfs(int v, std::vector <bool> &used, std::vector <int> &component){
        used[v] = 1;
        component.push_back(v);
        for (auto i : this->adj[v])
            if (!used[i.to]) dfs(i.to, used, component);
    }

    std::vector < std::vector <int> > search_component(){
        std::vector <bool> used;
        used.resize(this->number_vertex);
        std::vector <std::vector <int> > result;
        std::vector <int> component;
        for (int i = 0; i < this->number_vertex; ++i)
            if (!used[i]) {
                component.clear();
                dfs(i, used, component);
                result.push_back(component);
            }
        return result;
    }
    std::vector <int> bfs(int v){
        std::vector <int> dist;
        dist.resize(this->number_vertex);
        for (int i = 0; i < this->number_vertex; ++i)
            dist[i] = -1;
        dist[v] = 0;
        std::queue <int> q;
        q.push(v);
        while (!q.empty()){
            int cur = q.front();
            q.pop();
            for (auto i : this->adj[cur])
                if (dist[i.to] == -1){
                    dist[i.to] = dist[cur] + 1;
                    q.push(i.to);
                }
        }
        return dist;
    }

    std::vector <int> dijkstra(int v){
        std::vector <int> dist;
        dist.resize(this->number_vertex);
        for (int i = 0; i < this->number_vertex; ++i)
            dist[i] = -1;
        dist[v] = 0;
        std::priority_queue <std::pair <int, int> > q;
        q.push({0, v});
        while (!q.empty()){
            int cur = q.top().second;
            q.pop();
            for (auto i : this->adj[cur])
                if (dist[i.to] == -1 || dist[i.to] > dist[cur] + i.weight){
                    dist[i.to] = dist[cur] + i.weight;
                    q.push({-dist[i.to], i.to});
                }
        }
        return dist;
    }

    bool top_dfs (int v, std::vector <int>& used, std::vector <int> &ans) {
        used[v] = 1;
        bool result = 1;
        for (auto i : this->adj[v]) {
            if (!used[i.to]) {
                result = result  & top_dfs(i.to, used, ans);
            }
            else if (used[i.to] == 1) return 0;
        }
        used[v] = 2;
        ans.push_back(v);
        return result;
    }
    std::pair< bool, std::vector <int>> topological_sort() {
        int n = this->number_vertex;
        std::vector <int> used;
        used.resize(n);
        for (int i=0; i<n; ++i)
            used[i] = false;
        std::vector <int> result;
        bool answer = 1;
        for (int i=0; i<n; ++i)
            if (!used[i])
                answer &= top_dfs (i, used, result);
        reverse (result.begin(), result.end());
        return {answer, result};
    }
};



int main() {
    srand(time(0));
    return 0;
}
