//tasks - 1,2	6	13	14	18	19	22
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <cmath>
#include <ctime>
#include <windows.h>


struct graph_matrix{
    std::vector <std::vector < int > > matrix;
    int number_vertex;
    int number_edge;
    bool directed;
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
    void graph_random_weight(int v, int e, int o = 0){
        number_vertex = v;
        directed = o;
        number_edge = 0;
        matrix.clear();
        matrix.resize(number_vertex);
        for (int i = 0; i < number_vertex; ++i)
            matrix[i].resize(number_vertex);
        for (int i = 0; i < e; ++i){
            int from = rand() % number_vertex;
            int to = rand() % number_vertex;
            int weight = rand() % 1000;
            if (matrix[from][to]){//edge already init
                --i;
            }
            else {
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
};

struct edge{
    int to;
    int weight;
};

struct graph_adj{
    std::vector <std::vector < edge > > adj;
    int number_vertex;
    int number_edge;
    bool directed;
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
};

graph_matrix adj_to_matrix(graph_adj graph){
    graph_matrix result = graph_matrix(graph.number_vertex, graph.directed);
    for (int i = 0; i < graph.number_vertex; ++i){
        for (auto j : graph.adj[i])
            if (graph.directed || i < j.to) result.add(i, j.to, j.weight);
    }
    return result;
}

graph_adj matrix_to_adj(graph_matrix graph){
    graph_adj result = graph_adj(graph.number_vertex, graph.directed);
    for (int i = 0; i < graph.number_vertex; ++i){
        for (int j = 0; j < graph.number_vertex; ++j)
            if ((graph.matrix[i][j]) && (i < j || graph.directed)) result.add(i, j, graph.matrix[i][j]);
    }
    return result;
}


void dfs_adj(graph_adj &graf, int v, std::vector <bool> &used, std::vector <int> &component){
    used[v] = 1;
    component.push_back(v);
    for (auto i : graf.adj[v])
        if (!used[i.to]) dfs_adj(graf, i.to, used, component);
}

std::vector < std::vector <int> > search_component_adj(graph_adj graf){
    std::vector <bool> used;
    used.resize(graf.number_vertex);
    std::vector <std::vector <int> > result;
    std::vector <int> component;
    for (int i = 0; i < graf.number_vertex; ++i)
        if (!used[i]) {
            component.clear();
            dfs_adj(graf, i, used, component);
            result.push_back(component);
        }
    return result;
}

void dfs_matrix(graph_matrix &graf, int v, std::vector <bool> &used, std::vector <int> &component){
    used[v] = 1;
    component.push_back(v);
    for (int i = 0; i < graf.matrix[v].size(); ++i)
        if (graf.matrix[v][i] && !used[i]) dfs_matrix(graf, i, used, component);
}

std::vector < std::vector <int> > search_component_matrix(graph_matrix graf){
    std::vector <bool> used;
    used.resize(graf.number_vertex);
    std::vector <std::vector <int> > result;
    std::vector <int> component;
    for (int i = 0; i < graf.number_vertex; ++i)
        if (!used[i]) {
            component.clear();
            dfs_matrix(graf, i, used, component);
            result.push_back(component);
        }
    return result;
}

std::vector <int> bfs_adj(graph_adj graf, int v){
    std::vector <int> dist;
    dist.resize(graf.number_vertex);
    for (int i = 0; i < graf.number_vertex; ++i)
        dist[i] = -1;
    dist[v] = 0;
    std::queue <int> q;
    q.push(v);
    while (!q.empty()){
        int cur = q.front();
        q.pop();
        for (auto i : graf.adj[cur])
            if (dist[i.to] == -1){
                dist[i.to] = dist[cur] + 1;
                q.push(i.to);
            }
    }
    return dist;
}

std::vector <int> bfs_matrix(graph_matrix graf, int v){
    std::vector <int> dist;
    dist.resize(graf.number_vertex);
    for (int i = 0; i < graf.number_vertex; ++i)
        dist[i] = -1;
    dist[v] = 0;
    std::queue <int> q;
    q.push(v);
    while (!q.empty()){
        int cur = q.front();
        q.pop();
        for (int i = 0; i < graf.matrix[cur].size(); ++i)
            if (graf.matrix[cur][i] && dist[i] == -1){
                dist[i] = dist[cur] + 1;
                q.push(i);
            }
    }
    return dist;
}

std::vector <int> dijkstra_adj(graph_adj graf, int v){
    std::vector <int> dist;
    dist.resize(graf.number_vertex);
    for (int i = 0; i < graf.number_vertex; ++i)
        dist[i] = -1;
    dist[v] = 0;
    std::priority_queue <std::pair <int, int> > q;
    q.push({0, v});
    while (!q.empty()){
        int cur = q.top().second;
        q.pop();
        for (auto i : graf.adj[cur])
            if (dist[i.to] == -1 || dist[i.to] > dist[cur] + i.weight){
                dist[i.to] = dist[cur] + i.weight;
                q.push({-dist[i.to], i.to});
            }
    }
    return dist;
}

std::vector <int> dijkstra_matrix(graph_matrix graf, int v){
    std::vector <int> dist;
    dist.resize(graf.number_vertex);
    for (int i = 0; i < graf.number_vertex; ++i)
        dist[i] = -1;
    dist[v] = 0;
    std::priority_queue <std::pair <int, int> > q;
    q.push({0, v});
    while (!q.empty()){
        int cur = q.top().second;
        q.pop();
        for (int i = 0; i < graf.matrix[v].size(); ++i)
            if (graf.matrix[cur][i] && (dist[i] == -1|| dist[i] > dist[cur] + graf.matrix[cur][i])){
                dist[i] = dist[cur] + graf.matrix[cur][i];
                q.push({-dist[i], i});
            }
    }
    return dist;
}

bool top_dfs_adj (graph_adj &graf, int v, std::vector <int>& used, std::vector <int> &ans) {
    used[v] = 1;
    bool result = 1;
    for (auto i : graf.adj[v]) {
        if (!used[i.to]) {
            result = result  & top_dfs_adj(graf, i.to, used, ans);
        }
        else if (used[i.to] == 1) return 0;
    }
    used[v] = 2;
    ans.push_back(v);
    return result;
}

bool top_dfs_matrix (graph_matrix &graf, int v, std::vector <int>& used, std::vector <int> &ans) {
    used[v] = 1;
    bool answer = 1;
    for (int i = 0; i < graf.matrix[v].size(); ++i)
        if (graf.matrix[v][i] && !used[i])
            answer &= top_dfs_matrix(graf, i, used, ans);
        else if (graf.matrix[v][i] && used[i] == 1) return 0;
    ans.push_back(v);
    used[v] = 2;
    return answer;
}

std::pair< bool, std::vector <int>> topological_sort_adj(graph_adj graf) {
    int n = graf.number_vertex;
    std::vector <int> used;
    used.resize(n);
    for (int i=0; i<n; ++i)
        used[i] = false;
    std::vector <int> result;
    bool answer = 1;
    for (int i=0; i<n; ++i)
        if (!used[i])
            answer &= top_dfs_adj (graf, i, used, result);
    reverse (result.begin(), result.end());
    return {answer, result};
}

std::pair<bool, std::vector <int>> topological_sort_matrix(graph_matrix graf) {
    int n = graf.number_vertex;
    bool answer;
    std::vector <int> used;
    used.resize(n);
    for (int i=0; i<n; ++i)
        used[i] = false;
    std::vector <int> result;
    for (int i=0; i<n; ++i)
        if (!used[i])
            answer &= top_dfs_matrix (graf, i, used, result);
    reverse (result.begin(), result.end());
    return {answer, result};
}

struct span_edge{
    int from;
    int to;
    int weight;
};

bool operator <(span_edge a, span_edge b){
    return a.weight > b.weight;
}

void spanning_dfs_matrix(graph_matrix &graf, int v, std::vector <bool> &used, std::vector <span_edge> &result){
    used[v] = 1;
    for (int i = 0; i < graf.matrix[v].size(); ++i)
        if (graf.matrix[v][i] && !used[i]) {
            spanning_dfs_matrix(graf, i, used, result);
            result.push_back({v, i, graf.matrix[v][i]});
        }
}

void spanning_dfs_adj(graph_adj &graf, int v, std::vector <bool> &used, std::vector <span_edge> &result){
    used[v] = 1;
    for (auto i : graf.adj[v])
        if (!used[i.to]){
            result.push_back({v, i.to, i.weight});
            spanning_dfs_adj(graf, i.to, used, result);
        }
}


std::pair <std::vector <span_edge> , int > spanning_tree_adj(graph_adj graf){
    std::vector <span_edge> result;
    std::vector <bool> used;
    used.resize(graf.number_vertex);
    spanning_dfs_adj(graf, 0, used, result);
    int weight = 0;
    for (auto i : result)
        weight += i.weight;
    return {result, weight};
}

std::pair <std::vector <span_edge> , int > spanning_tree_matrix(graph_matrix graf){
    std::vector <span_edge> result;
    std::vector <bool> used;
    used.resize(graf.number_vertex);
    spanning_dfs_matrix(graf, 0, used, result);
    int weight = 0;
    for (auto i : result)
        weight += i.weight;
    return {result, weight};
}

std::pair <std::vector <span_edge> , int > minimal_spanning_tree_adj(graph_adj graf){
    std::vector <span_edge> result;
    std::vector <int> dist;
    std::vector <int> used;
    used.resize(graf.number_vertex);
    dist.resize(graf.number_vertex);
    for (int i = 0; i < graf.number_vertex; ++i) {
        dist[i] = -1;
        used[i] = 0;
    }
    dist[0] = 0;
    std::priority_queue <span_edge> q;
    q.push({0, 0, 0});
    while (!q.empty()){
        int cur = q.top().to;
        span_edge e = q.top();
        q.pop();
        if (used[cur]) continue;
        result.push_back(e);
        used[cur] = 1;
        for (auto i : graf.adj[cur])
            if ((dist[i.to] == -1 || dist[i.to] > i.weight) && !used[i.to]){
                dist[i.to] = i.weight;
                q.push({cur, i.to, i.weight});
            }
    }
    result.erase(result.begin());
    int total = 0;
    for (auto i : result)
        total += i.weight;
    return {result, total};
}

std::pair <std::vector <span_edge> , int > minimal_spanning_tree_matrix(graph_matrix graf){
    std::vector <span_edge> result;
    std::vector <int> dist;
    std::vector <int> used;
    used.resize(graf.number_vertex);
    dist.resize(graf.number_vertex);
    for (int i = 0; i < graf.number_vertex; ++i) {
        dist[i] = -1;
        used[i] = 0;
    }
    dist[0] = 0;
    std::priority_queue <span_edge> q;
    q.push({0, 0, 0});
    while (!q.empty()){
        int cur = q.top().to;
        span_edge e = q.top();
        q.pop();
        if (used[cur]) continue;
        result.push_back(e);
        used[cur] = 1;
        for (int i = 0; i < graf.matrix[cur].size(); ++i)
            if (graf.matrix[cur][i] && ((dist[i] == -1 || dist[i] > graf.matrix[cur][i]) && !used[i])){
                dist[i] = graf.matrix[cur][i];
                q.push({cur, i, graf.matrix[cur][i]});
            }
    }
    result.erase(result.begin());
    int total = 0;
    for (auto i : result)
        total += i.weight;
    return {result, total};
}

void interactor_adj() {
    std::cout << "Is graph directed? Press y/n\n";
    char is_directed;
    std::cin >> is_directed;
    std::cout << "Print number of vertexes\n";
    int n;
    std::cin >> n;
    graph_adj graph = graph_adj(n, is_directed == 'y');
    std::cout << "Press y/n if edges have weight\n";
    char weight;
    std::cin >> weight;
    bool is_weight = weight == 'y';
    while (1){
        std::string command;
        std::cout << "Please, print the command\n";
        std::cin >> command;
        if (command == "exit") break;
        if (command == "add"){
            int from, to;
            std::cin >> from >> to;
            if (is_weight) {
                int w;
                std::cin >> w;
                graph.add(from, to , w);
            }
            else {
                graph.add(from, to);
            }
            std::cout << "Done\n";

        }
        if (command == "search_component"){
            std::vector <std::vector <int> > result = search_component_adj(graph);
            std::cout << "Components:\n";
            for (auto i : result){
                for (auto j : i)
                    std::cout << j << " ";
                std::cout << "\n";
            }
            std::cout << "Done\n";
        }
        if (command == "bfs"){
            int v;
            std::cin >> v;
            std::vector <int> dist = bfs_adj(graph, v);
            std::cout << "Vector of distance from " << v << " to others:\n";
            for (int i = 0; i < dist.size(); ++i){
                std::cout << "for " <<i << " : " << dist[i] << "\n";
            }
            std::cout << "\nDone\n";
        }
        if (command == "dijkstra"){
            int v;
            std::cin >> v;
            std::vector <int> dist = dijkstra_adj(graph, v);
            std::cout << "Vector of distance from " << v << " to others:\n";
            for (int i = 0; i < dist.size(); ++i){
                std::cout << "for " <<i << " : " << dist[i] << "\n";
            }
            std::cout << "\nDone\n";
        }
        if (command == "top_sort"){
            std::pair<bool, std::vector <int>> result = topological_sort_adj(graph);
            if (!result.first){
                std::cout << "No result\n";
                continue;
            }
            std::cout << "Result :\n";
            for (auto i : result.second)
                std::cout << i << " ";
            std::cout << "\nDone\n";
        }
        if (command == "spanning_tree"){
            std::pair < std::vector <span_edge>, int> ans = spanning_tree_adj(graph);
            std::cout << "Weight of tree : " << ans.second << "\n";
            std::cout << "Tree :\n";
            for (auto i : ans.first){
                std::cout << "from " << i.from << " to " << i.to << " weight is " << i.weight << "\n";
            }
            std::cout << "Done\n";
        }
        if (command == "min_spanning_tree"){
            std::pair < std::vector <span_edge>, int> ans = minimal_spanning_tree_adj(graph);
            std::cout << "Weight of tree : " << ans.second << "\n";
            std::cout << "Tree :\n";
            for (auto i : ans.first){
                std::cout << "from " << i.from << " to " << i.to << " weight is " << i.weight << "\n";
            }
            std::cout << "Done\n";
        }
    }
}

void interactor_matrix(){
    std::cout << "Is graph directed? Press y/n\n";
    char is_directed;
    std::cin >> is_directed;
    std::cout << "Print number of vertexes\n";
    int n;
    std::cin >> n;
    graph_matrix graph = graph_matrix(n, is_directed == 'y');
    std::cout << "Press y/n if edges have weight\n";
    char weight;
    std::cin >> weight;
    bool is_weight = weight == 'y';
    while (1){
        std::string command;
        std::cout << "Please, print the command\n";
        std::cin >> command;
        if (command == "exit") break;
        if (command == "add"){
            int from, to;
            std::cin >> from >> to;
            if (is_weight) {
                int w;
                std::cin >> w;
                graph.add(from, to , w);
            }
            else {
                graph.add(from, to);
            }
            std::cout << "Done\n";

        }
        if (command == "search_component"){
            std::vector <std::vector <int> > result = search_component_matrix(graph);
            std::cout << "Components:\n";
            for (auto i : result){
                for (auto j : i)
                    std::cout << j << " ";
                std::cout << "\n";
            }
            std::cout << "Done\n";
        }
        if (command == "bfs"){
            int v;
            std::cin >> v;
            std::vector <int> dist = bfs_matrix(graph, v);
            std::cout << "Vector of distance from " << v << " to others:\n";
            for (int i = 0; i < dist.size(); ++i){
                std::cout << "for " <<i << " : " << dist[i] << "\n";
            }
            std::cout << "\nDone\n";
        }
        if (command == "dijkstra"){
            int v;
            std::cin >> v;
            std::vector <int> dist = dijkstra_matrix(graph, v);
            std::cout << "Vector of distance from " << v << " to others:\n";
            for (int i = 0; i < dist.size(); ++i){
                std::cout << "for " <<i << " : " << dist[i] << "\n";
            }
            std::cout << "\nDone\n";
        }
        if (command == "top_sort"){
            std::pair<bool, std::vector <int>> result = topological_sort_matrix(graph);
            if (!result.first){
                std::cout << "No result\n";
                continue;
            }
            std::cout << "Result :\n";
            for (auto i : result.second)
                std::cout << i << " ";
            std::cout << "\nDone\n";
        }
        if (command == "spanning_tree"){
            std::pair < std::vector <span_edge>, int> ans = spanning_tree_matrix(graph);
            std::cout << "Weight of tree : " << ans.second << "\n";
            std::cout << "Tree :\n";
            for (auto i : ans.first){
                std::cout << "from " << i.from << " to " << i.to << " weight is " << i.weight << "\n";
            }
            std::cout << "Done\n";
        }
        if (command == "min_spanning_tree"){
            std::pair < std::vector <span_edge>, int> ans = minimal_spanning_tree_matrix(graph);
            std::cout << "Weight of tree : " << ans.second << "\n";
            std::cout << "Tree :\n";
            for (auto i : ans.first){
                std::cout << "from " << i.from << " to " << i.to << " weight is " << i.weight << "\n";
            }
            std::cout << "Done\n";
        }
    }
};

void interactor(){
    printf("------------INERACTOR MODE------------\n");
    std::cout << "To use matrix press 'm'\nTo use list press 'l'\n";
    char type;
    std::cin >> type;
    if (type == 'm') interactor_matrix();
    if (type == 'l') interactor_adj();
}

void benchmark(){
    std::cout << "----------------BENCHMARK MODE----------------\n";
    for (int n = 10; n <= 10000; n *= 10){
        std::cout << "Number of vertex is " << n << "\n";
        for (int m = n; m < n * (n - 1) / 2; m *= 5){
            std::cout << "   Number of edges is " << m << "\n";
            graph_adj adj;
            adj.graph_random_weight(n, m);
            graph_matrix matrix = adj_to_matrix(adj);
            int start_adj = clock();
            std::vector <std::vector <int>> temp = search_component_adj(adj);
            int end_adj = clock();
            int start_matrix = clock();
            temp = search_component_matrix(matrix);
            int end_matrix = clock();
            std::cout << "       Time searching component: list - " << -(start_adj - end_adj)/1000.0 << "\n";
            std::cout << "                                 matrix - " << -(start_matrix - end_matrix)/1000.0 << "\n";
            start_adj = clock();
            std::vector <int> dist = bfs_adj(adj, 0);
            end_adj = clock();
            start_matrix = clock();
            dist = bfs_matrix(matrix, 0);
            end_matrix = clock();
            std::cout << "       Time working bfs: list - " << -(start_adj - end_adj)/1000.0 << "\n";
            std::cout << "                         matrix - " << -(start_matrix - end_matrix)/1000.0 << "\n";
            start_adj = clock();
            std::pair<bool, std::vector <int> >  top_sort = topological_sort_adj(adj);
            end_adj = clock();
            start_matrix = clock();
            top_sort = topological_sort_matrix(matrix);
            end_matrix = clock();
            std::cout << "       Time working topological sort: list - " << -(start_adj - end_adj)/1000.0 << "\n";
            std::cout << "                                      matrix - " << -(start_matrix - end_matrix)/1000.0 << "\n";
            if (n <= 1000){
                start_adj = clock();
                std::vector <int>  dijkstra = dijkstra_adj(adj, 0);
                end_adj = clock();
                start_matrix = clock();
                dijkstra = dijkstra_matrix(matrix, 0);
                end_matrix = clock();
                std::cout << "       Time working dijkstra : list - " << -(start_adj - end_adj)/1000.0 << "\n";
                std::cout << "                               matrix - " << -(start_matrix - end_matrix)/1000.0 << "\n";
            }
            start_adj = clock();
            std::pair< std::vector <span_edge>, int > span = spanning_tree_adj(adj);
            end_adj = clock();
            start_matrix = clock();
            span = spanning_tree_matrix(matrix);
            end_matrix = clock();
            std::cout << "       Time searching spanning tree : list - " << -(start_adj - end_adj)/1000.0 << "\n";
            std::cout << "                                      matrix - " << -(start_matrix - end_matrix)/1000.0 << "\n";
            if (n <= 1000){
                start_adj = clock();
                span = minimal_spanning_tree_adj(adj);
                end_adj = clock();
                start_matrix = clock();
                span = minimal_spanning_tree_matrix(matrix);
                end_matrix = clock();
                std::cout << "       Time searching minimal spanning tree : list - " << -(start_adj - end_adj)/1000.0 << "\n";
                std::cout << "                                              matrix - " << -(start_matrix - end_matrix)/1000.0 << "\n";
            }
        }
    }
}

void visual(){
    std::cout << "------------VISUAL MODE-------------\n";
    std::cout << "1. Searching connected components \n";
    graph_adj graph = graph_adj(7, 0);
    graph.add(0, 1);
    graph.add(0, 2);
    graph.add(0, 3);
    graph.add(1, 2);
    graph.add(1, 3);
    graph.add(3, 6);
    graph.add(4, 5);
    graph.print();
    std::vector <std::vector <int> > components = search_component_adj(graph);
    std::cout << "Components: ";
    std::cout << components.size() << "\n";
    for (auto i : components){
        for (auto j : i)
            std::cout << j << " ";
        std::cout << "\n";
    }
    Sleep(3 * 1000);
    std::cout << "2. BFS algorithm\n";
    graph.add(4, 2);
    graph.print();
    std::vector <int> dist = bfs_adj(graph, 2);
    std::cout << "Distance from vertex 2: \n";
    for (int i = 0; i < 7; ++i)
        std::cout << "to " << i << " is " << dist[i] << "\n";
    Sleep(3 * 1000);
    std::cout << "3. Topological sort\n";
    graph_adj top = graph_adj(7, 1);
    top.add(0, 1);
    top.add(0, 2);
    top.add(0, 3);
    top.add(1, 2);
    top.add(1, 3);
    top.add(3, 6);
    top.add(4, 5);
    top.add(4, 2);
    top.print();
    std::pair <bool, std::vector <int>> sort = topological_sort_adj(top);
    std::cout << "Correct order: ";
    for (auto i : sort.second)
        std::cout << i << " ";
    std::cout << "\n";
    Sleep(3 * 1000);
    std::cout << "4. Dijkstra\n";
    graph_matrix weight = graph_matrix(7, 0);
    weight.add(0, 1, 10);
    weight.add(0, 2, 3);
    weight.add(0, 3, 100);
    weight.add(1, 2, 102);
    weight.add(1, 3, 23);
    weight.add(3, 6, 14);
    weight.add(4, 5, 32);
    weight.add(4, 2, 34);
    weight.add(4, 0, 44);
    weight.add(4, 6, 2);
    weight.add(4, 1, 1);
    weight.print();
    dist = dijkstra_matrix(weight, 3);
    std::cout << "Distance from vertex 3: \n";
    for (int i = 0; i < 7; ++i)
        std::cout << "to " << i << " is " << dist[i] << "\n";
    Sleep(3 * 1000);
    std::cout << "5. Spanning tree algorithm \n";
    weight.print();
    std::pair < std::vector <span_edge>, int> result = spanning_tree_matrix(weight);
    std::cout << "Tree with weight " << result.second << "\nEdges:\n";
    for (auto i : result.first)
        std::cout << "(" << i.from << ", " << i.to << ")" << " " << i.weight << "\n";
    Sleep(3 * 1000);
    std::cout << "6. Minimal spanning tree algorithm \n";
    weight.print();
    result = minimal_spanning_tree_matrix(weight);
    std::cout << "Tree with weight " << result.second << "\nEdges:\n";
    for (auto i : result.first)
        std::cout << "(" << i.from << ", " << i.to << ")" << " " << i.weight << "\n";
    std::cout << "Have a nice day!\n";
}

void selector(){
    printf("Press 'i' to interactor mode\nPress 'v' to visual mode\nPress 'b' to benchmark mode\n");
    char mode;
    std::cin >> mode;
    if (mode == 'i') interactor();
    if (mode == 'b') benchmark();
    if (mode == 'v') visual();
}


int main() {
    srand(time(0));
    selector();

    return 0;
}
