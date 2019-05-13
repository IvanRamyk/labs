//tasks - 1,2	6	13	14	18	19	22
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <cmath>
#include <ctime>
#include <windows.h>

using namespace std;

struct graph_matrix{
    vector <vector < int > > matrix;
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
        matrix.resize(number_vertex);
        for (int i = 0; i < number_vertex; ++i)
            matrix[i].resize(number_vertex);
    }
    void add(int from, int to, int weight = 1){
        matrix[from][to] = weight;
        if (!directed)
            matrix[to][from] = weight;
        ++number_edge;
    }
    void graph_random(int v, int e, int o = 0){
        number_vertex = v;
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
};

struct edge{
    int to;
    int weight;
};

struct graph_adj{
    vector <vector < edge > > adj;
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
        adj.resize(number_vertex);
    }
    void add(int from, int to, int weight = 1){
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
};

graph_matrix adj_to_matrix(graph_adj graph){
    graph_matrix result = graph_matrix(graph.number_vertex, graph.directed);
    for (int i = 0; i < graph.number_vertex; ++i){
        for (auto j : graph.adj[i])
            result.add(i, j.to, j.weight);
    }
    return result;
}

graph_adj matrix_to_adj(graph_matrix graph){
    graph_adj result = graph_adj(graph.number_vertex, graph.directed);
    for (int i = 0; i < graph.number_vertex; ++i){
        for (int j = 0; j < graph.number_vertex; ++j)
            if (graph.matrix[i][j]) result.add(i, j, graph.matrix[i][j]);
    }
    return result;
}


void dfs_adj(graph_adj &graf, int v, vector <bool> &used, vector <int> &component){
    used[v] = 1;
    component.push_back(v);
    for (auto i : graf.adj[v])
        if (!used[i.to]) dfs_adj(graf, i.to, used, component);
}

vector < vector <int> > search_component_adj(graph_adj graf){
    vector <bool> used;
    used.resize(graf.number_vertex);
    vector <vector <int> > result;
    vector <int> component;
    for (int i = 0; i < graf.number_vertex; ++i)
        if (!used[i]) {
            component.clear();
            dfs_adj(graf, i, used, component);
            result.push_back(component);
        }
    return result;
}

void dfs_matrix(graph_matrix &graf, int v, vector <bool> &used, vector <int> &component){
    used[v] = 1;
    component.push_back(v);
    for (int i = 0; i < graf.matrix[v].size(); ++i)
        if (graf.matrix[v][i] && !used[i]) dfs_matrix(graf, i, used, component);
}

vector < vector <int> > search_component_matrix(graph_matrix graf){
    vector <bool> used;
    used.resize(graf.number_vertex);
    vector <vector <int> > result;
    vector <int> component;
    for (int i = 0; i < graf.number_vertex; ++i)
        if (!used[i]) {
            component.clear();
            dfs_matrix(graf, i, used, component);
            result.push_back(component);
        }
    return result;
}

vector <int> bfs_adj(graph_adj graf, int v){
    vector <int> dist;
    dist.resize(graf.number_vertex);
    for (int i = 0; i < graf.number_vertex; ++i)
        dist[i] = -1;
    dist[v] = 0;
    queue <int> q;
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

vector <int> bfs_matrix(graph_matrix graf, int v){
    vector <int> dist;
    dist.resize(graf.number_vertex);
    for (int i = 0; i < graf.number_vertex; ++i)
        dist[i] = -1;
    dist[v] = 0;
    queue <int> q;
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

vector <int> dijkstra_adj(graph_adj graf, int v){
    vector <int> dist;
    dist.resize(graf.number_vertex);
    for (int i = 0; i < graf.number_vertex; ++i)
        dist[i] = -1;
    dist[v] = 0;
    priority_queue <pair <int, int> > q;
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

vector <int> dijkstra_matrix(graph_matrix graf, int v){
    vector <int> dist;
    dist.resize(graf.number_vertex);
    for (int i = 0; i < graf.number_vertex; ++i)
        dist[i] = -1;
    dist[v] = 0;
    priority_queue <pair <int, int> > q;
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

bool top_dfs_adj (graph_adj &graf, int v, vector <int>& used, vector <int> &ans) {
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

bool top_dfs_matrix (graph_matrix &graf, int v, vector <int>& used, vector <int> &ans) {
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

pair< bool, vector <int>> topological_sort_adj(graph_adj graf) {
    int n = graf.number_vertex;
    vector <int> used;
    used.resize(n);
    for (int i=0; i<n; ++i)
        used[i] = false;
    vector <int> result;
    bool answer = 1;
    for (int i=0; i<n; ++i)
        if (!used[i])
            answer &= top_dfs_adj (graf, i, used, result);
    reverse (result.begin(), result.end());
    return {answer, result};
}

pair<bool, vector <int>> topological_sort_matrix(graph_matrix graf) {
    int n = graf.number_vertex;
    bool answer;
    vector <int> used;
    used.resize(n);
    for (int i=0; i<n; ++i)
        used[i] = false;
    vector <int> result;
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

void spanning_dfs_matrix(graph_matrix &graf, int v, vector <bool> &used, vector <span_edge> &result){
    used[v] = 1;
    for (int i = 0; i < graf.matrix[v].size(); ++i)
        if (graf.matrix[v][i] && !used[i]) {
            spanning_dfs_matrix(graf, i, used, result);
            result.push_back({v, i, graf.matrix[v][i]});
        }
}

void spanning_dfs_adj(graph_adj &graf, int v, vector <bool> &used, vector <span_edge> &result){
    used[v] = 1;
    for (auto i : graf.adj[v])
        if (!used[i.to]){
            result.push_back({v, i.to, i.weight});
            spanning_dfs_adj(graf, i.to, used, result);
        }
}


pair <vector <span_edge> , int > spanning_tree_adj(graph_adj graf){
    vector <span_edge> result;
    vector <bool> used;
    used.resize(graf.number_vertex);
    spanning_dfs_adj(graf, 0, used, result);
    int weight = 0;
    for (auto i : result)
        weight += i.weight;
    return {result, weight};
}

pair <vector <span_edge> , int > spanning_tree_matrix(graph_matrix graf){
    vector <span_edge> result;
    vector <bool> used;
    used.resize(graf.number_vertex);
    spanning_dfs_matrix(graf, 0, used, result);
    int weight = 0;
    for (auto i : result)
        weight += i.weight;
    return {result, weight};
}

pair <vector <span_edge> , int > minimal_spanning_tree_adj(graph_adj graf){
    vector <span_edge> result;
    vector <int> dist;
    vector <int> used;
    used.resize(graf.number_vertex);
    dist.resize(graf.number_vertex);
    for (int i = 0; i < graf.number_vertex; ++i) {
        dist[i] = -1;
        used[i] = 0;
    }
    dist[0] = 0;
    priority_queue <span_edge> q;
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

pair <vector <span_edge> , int > minimal_spanning_tree_matrix(graph_matrix graf){
    vector <span_edge> result;
    vector <int> dist;
    vector <int> used;
    used.resize(graf.number_vertex);
    dist.resize(graf.number_vertex);
    for (int i = 0; i < graf.number_vertex; ++i) {
        dist[i] = -1;
        used[i] = 0;
    }
    dist[0] = 0;
    priority_queue <span_edge> q;
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
    cout << "Is graph directed? Press y/n\n";
    char is_directed;
    cin >> is_directed;
    cout << "Print number of vertexes\n";
    int n;
    cin >> n;
    graph_adj graph = graph_adj(n, is_directed == 'y');
    cout << "Press y/n if edges have weight\n";
    char weight;
    cin >> weight;
    bool is_weight = weight == 'y';
    while (1){
        string command;
        cout << "Please, print the command\n";
        cin >> command;
        if (command == "exit") break;
        if (command == "add"){
            int from, to;
            cin >> from >> to;
            if (is_weight) {
                int w;
                cin >> w;
                graph.add(from, to , w);
            }
            else {
                graph.add(from, to);
            }
            cout << "Done\n";

        }
        if (command == "search_component"){
            vector <vector <int> > result = search_component_adj(graph);
            cout << "Components:\n";
            for (auto i : result){
                for (auto j : i)
                    cout << j << " ";
                cout << "\n";
            }
            cout << "Done\n";
        }
        if (command == "bfs"){
            int v;
            cin >> v;
            vector <int> dist = bfs_adj(graph, v);
            cout << "Vector of distance from " << v << " to others:\n";
            for (int i = 0; i < dist.size(); ++i){
                cout << "for " <<i << " : " << dist[i] << "\n";
            }
            cout << "\nDone\n";
        }
        if (command == "dijkstra"){
            int v;
            cin >> v;
            vector <int> dist = dijkstra_adj(graph, v);
            cout << "Vector of distance from " << v << " to others:\n";
            for (int i = 0; i < dist.size(); ++i){
                cout << "for " <<i << " : " << dist[i] << "\n";
            }
            cout << "\nDone\n";
        }
        if (command == "top_sort"){
            pair<bool, vector <int>> result = topological_sort_adj(graph);
            if (!result.first){
                cout << "No result\n";
                continue;
            }
            cout << "Result :\n";
            for (auto i : result.second)
                cout << i << " ";
            cout << "\nDone\n";
        }
        if (command == "spanning_tree"){
            pair < vector <span_edge>, int> ans = spanning_tree_adj(graph);
            cout << "Weight of tree : " << ans.second << "\n";
            cout << "Tree :\n";
            for (auto i : ans.first){
                cout << "from " << i.from << " to " << i.to << " weight is " << i.weight << "\n";
            }
            cout << "Done\n";
        }
        if (command == "min_spanning_tree"){
            pair < vector <span_edge>, int> ans = minimal_spanning_tree_adj(graph);
            cout << "Weight of tree : " << ans.second << "\n";
            cout << "Tree :\n";
            for (auto i : ans.first){
                cout << "from " << i.from << " to " << i.to << " weight is " << i.weight << "\n";
            }
            cout << "Done\n";
        }
    }
}

void interactor_matrix(){
    cout << "Is graph directed? Press y/n\n";
    char is_directed;
    cin >> is_directed;
    cout << "Print number of vertexes\n";
    int n;
    cin >> n;
    graph_matrix graph = graph_matrix(n, is_directed == 'y');
    cout << "Press y/n if edges have weight\n";
    char weight;
    cin >> weight;
    bool is_weight = weight == 'y';
    while (1){
        string command;
        cout << "Please, print the command\n";
        cin >> command;
        if (command == "exit") break;
        if (command == "add"){
            int from, to;
            cin >> from >> to;
            if (is_weight) {
                int w;
                cin >> w;
                graph.add(from, to , w);
            }
            else {
                graph.add(from, to);
            }
            cout << "Done\n";

        }
        if (command == "search_component"){
            vector <vector <int> > result = search_component_matrix(graph);
            cout << "Components:\n";
            for (auto i : result){
                for (auto j : i)
                    cout << j << " ";
                cout << "\n";
            }
            cout << "Done\n";
        }
        if (command == "bfs"){
            int v;
            cin >> v;
            vector <int> dist = bfs_matrix(graph, v);
            cout << "Vector of distance from " << v << " to others:\n";
            for (int i = 0; i < dist.size(); ++i){
                cout << "for " <<i << " : " << dist[i] << "\n";
            }
            cout << "\nDone\n";
        }
        if (command == "dijkstra"){
            int v;
            cin >> v;
            vector <int> dist = dijkstra_matrix(graph, v);
            cout << "Vector of distance from " << v << " to others:\n";
            for (int i = 0; i < dist.size(); ++i){
                cout << "for " <<i << " : " << dist[i] << "\n";
            }
            cout << "\nDone\n";
        }
        if (command == "top_sort"){
            pair<bool, vector <int>> result = topological_sort_matrix(graph);
            if (!result.first){
                cout << "No result\n";
                continue;
            }
            cout << "Result :\n";
            for (auto i : result.second)
                cout << i << " ";
            cout << "\nDone\n";
        }
        if (command == "spanning_tree"){
            pair < vector <span_edge>, int> ans = spanning_tree_matrix(graph);
            cout << "Weight of tree : " << ans.second << "\n";
            cout << "Tree :\n";
            for (auto i : ans.first){
                cout << "from " << i.from << " to " << i.to << " weight is " << i.weight << "\n";
            }
            cout << "Done\n";
        }
        if (command == "min_spanning_tree"){
            pair < vector <span_edge>, int> ans = minimal_spanning_tree_matrix(graph);
            cout << "Weight of tree : " << ans.second << "\n";
            cout << "Tree :\n";
            for (auto i : ans.first){
                cout << "from " << i.from << " to " << i.to << " weight is " << i.weight << "\n";
            }
            cout << "Done\n";
        }
    }
};

void interactor(){
    printf("------------INERACTOR MODE------------\n");
    cout << "To use matrix press 'm'\nTo use list press 'l'\n";
    char type;
    cin >> type;
    if (type == 'm') interactor_matrix();
    if (type == 'l') interactor_adj();
}

void benchmark(){
    cout << "----------------BENCHMARK MODE----------------\n";
    for (int n = 10; n <= 10000; n *= 10){
        cout << "Number of vertex is " << n << "\n";
        for (int m = n; m < n * (n - 1) / 2; m *= 5){
            cout << "   Number of edges is " << m << "\n";
            graph_adj adj;
            adj.graph_random_weight(n, m);
            graph_matrix matrix = adj_to_matrix(adj);
            int start_adj = clock();
            vector <vector <int>> temp = search_component_adj(adj);
            int end_adj = clock();
            int start_matrix = clock();
            temp = search_component_matrix(matrix);
            int end_matrix = clock();
            cout << "       Time searching component: list - " << -(start_adj - end_adj)/1000.0 << "\n";
            cout << "                                 matrix - " << -(start_matrix - end_matrix)/1000.0 << "\n";
            start_adj = clock();
            vector <int> dist = bfs_adj(adj, 0);
            end_adj = clock();
            start_matrix = clock();
            dist = bfs_matrix(matrix, 0);
            end_matrix = clock();
            cout << "       Time working bfs: list - " << -(start_adj - end_adj)/1000.0 << "\n";
            cout << "                         matrix - " << -(start_matrix - end_matrix)/1000.0 << "\n";
            start_adj = clock();
            pair<bool, vector <int> >  top_sort = topological_sort_adj(adj);
            end_adj = clock();
            start_matrix = clock();
            top_sort = topological_sort_matrix(matrix);
            end_matrix = clock();
            cout << "       Time working topological sort: list - " << -(start_adj - end_adj)/1000.0 << "\n";
            cout << "                                      matrix - " << -(start_matrix - end_matrix)/1000.0 << "\n";
            if (n <= 1000){
                start_adj = clock();
                vector <int>  dijkstra = dijkstra_adj(adj, 0);
                end_adj = clock();
                start_matrix = clock();
                dijkstra = dijkstra_matrix(matrix, 0);
                end_matrix = clock();
                cout << "       Time working dijkstra : list - " << -(start_adj - end_adj)/1000.0 << "\n";
                cout << "                               matrix - " << -(start_matrix - end_matrix)/1000.0 << "\n";
            }
            start_adj = clock();
            pair< vector <span_edge>, int > span = spanning_tree_adj(adj);
            end_adj = clock();
            start_matrix = clock();
            span = spanning_tree_matrix(matrix);
            end_matrix = clock();
            cout << "       Time searching spanning tree : list - " << -(start_adj - end_adj)/1000.0 << "\n";
            cout << "                                      matrix - " << -(start_matrix - end_matrix)/1000.0 << "\n";
            if (n <= 1000){
                start_adj = clock();
                span = minimal_spanning_tree_adj(adj);
                end_adj = clock();
                start_matrix = clock();
                span = minimal_spanning_tree_matrix(matrix);
                end_matrix = clock();
                cout << "       Time searching minimal spanning tree : list - " << -(start_adj - end_adj)/1000.0 << "\n";
                cout << "                                              matrix - " << -(start_matrix - end_matrix)/1000.0 << "\n";
            }
        }
    }
}

void visual(){
    
}

void selector(){
    printf("Press 'i' to interactor mode\nPress 'v' to visual mode\nPress 'b' to benchmark mode\n");
    char mode;
    cin >> mode;
    if (mode == 'i') interactor();
    if (mode == 'b') benchmark();
}


int main() {
    srand(time(0));
    selector();

    return 0;
}
