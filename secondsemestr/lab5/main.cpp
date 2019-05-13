#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <cmath>
#include <ctime>
#include <windows.h>

using namespace std;

struct graf_matrix{
    vector <vector < int > > matrix;
    int number_vertex;
    int number_edge;
    bool orient;
    graf_matrix(){
        number_edge = 0;
        number_vertex = 0;
        matrix.clear();
        orient = 0;
    }
    graf_matrix(int v, bool o = 0){
        orient = 0;
        number_vertex = v;
        matrix.resize(number_vertex);
        for (int i = 0; i < number_vertex; ++i)
            matrix[i].resize(number_vertex);
    }
    void add(int from, int to, int weight = 1){
        matrix[from][to] = weight;
        if (!orient)
            matrix[to][from] = weight;
        ++number_edge;
    }
    void graf_random(int v, int e, int o = 0){
        number_vertex = v;
        number_edge = e;
        orient = o;
        for (int i = 0; i < number_edge; ++i){
            int from = rand() % number_edge;
            int to = rand() % number_edge;
            if (matrix[from][to]){//edge already init
                --i;
            }
            else {
                add(from, to, 1);
            }
        }
    }
};

struct edge{
    int to;
    int weight;
};

struct graf_adj{
    vector <vector < edge > > adj;
    int number_vertex;
    int number_edge;
    bool orient;
    graf_adj(){
        number_edge = 0;
        number_vertex = 0;
        adj.clear();
        orient = 0;
    }
    graf_adj(int v, bool o = 0){
        orient = o;
        number_vertex = v;
        adj.resize(number_vertex);
    }
    void add(int from, int to, int weight = 1){
        adj[from].push_back({to,weight});
        if (!orient)
            adj[to].push_back({from,weight});
        ++number_edge;
    }
    void graf_random(int v, int e, int o = 0){
        number_vertex = v;
        number_edge = e;
        orient = o;
        for (int i = 0; i < number_edge; ++i){
            int from = rand() % number_edge;
            int to = rand() % number_edge;
            add(from, to, 1);
        }
    }
};

void dfs_adj(graf_adj &graf, int v, vector <bool> &used, vector <int> &component){
    used[v] = 1;
    component.push_back(v);
    for (auto i : graf.adj[v])
        if (!used[i.to]) dfs_adj(graf, i.to, used, component);
}

vector < vector <int> > search_component_adj(graf_adj graf){
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

void dfs_matrix(graf_matrix &graf, int v, vector <bool> &used, vector <int> &component){
    used[v] = 1;
    component.push_back(v);
    for (int i = 0; i < graf.matrix[v].size(); ++i)
        if (graf.matrix[v][i] && !used[i]) dfs_matrix(graf, i, used, component);
}

vector < vector <int> > search_component_matrix(graf_matrix graf){
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

vector <int> bfs_adj(graf_adj graf, int v){
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

vector <int> bfs_matrix(graf_matrix graf, int v){
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
        for (int i = 0; i < graf.matrix[v].size(); ++i)
            if (graf.matrix[cur][i] && dist[i] == -1){
                dist[i] = dist[cur] + 1;
                q.push(i);
            }
    }
    return dist;
}

vector <int> dijkstra_adj(graf_adj graf, int v){
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

vector <int> dijkstra_matrix(graf_matrix graf, int v){
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

void top_dfs_adj (graf_adj &graf, int v, vector <bool>& used, vector <int> &ans) {
    used[v] = true;
    for (auto i : graf.adj[v]) {
        if (!used[i.to]) {
            top_dfs_adj(graf, i.to, used, ans);
        }
    }
    ans.push_back(v);
}

void top_dfs_matrix (graf_matrix &graf, int v, vector <bool>& used, vector <int> &ans) {
    used[v] = true;
    for (int i = 0; i < graf.matrix[v].size(); ++i)
        if (graf.matrix[v][i] && !used[i])
            top_dfs_matrix(graf, i, used, ans);
    ans.push_back(v);
}

vector <int> topological_sort_adj(graf_adj graf) {
    int n = graf.number_vertex;
    vector <bool> used;
    used.resize(n);
    for (int i=0; i<n; ++i)
        used[i] = false;
    vector <int> result;
    for (int i=0; i<n; ++i)
        if (!used[i])
            top_dfs_adj (graf, i, used, result);
    reverse (result.begin(), result.end());
    return result;
}

vector <int> topological_sort_matrix(graf_matrix graf) {
    int n = graf.number_vertex;
    vector <bool> used;
    used.resize(n);
    for (int i=0; i<n; ++i)
        used[i] = false;
    vector <int> result;
    for (int i=0; i<n; ++i)
        if (!used[i])
            top_dfs_matrix (graf, i, used, result);
    reverse (result.begin(), result.end());
    return result;
}

struct span_edge{
    int from;
    int to;
    int weight;
};

bool operator <(span_edge a, span_edge b){
    return a.weight > b.weight;
}

void spanning_dfs_matrix(graf_matrix &graf, int v, vector <bool> &used, vector <span_edge> &result){
    used[v] = 1;
    for (int i = 0; i < graf.matrix[v].size(); ++i)
        if (graf.matrix[v][i] && !used[i]) {
            spanning_dfs_matrix(graf, i, used, result);
            result.push_back({v, i, graf.matrix[v][i]});
        }
}

void spanning_dfs_adj(graf_adj &graf, int v, vector <bool> &used, vector <span_edge> &result){
    used[v] = 1;
    for (auto i : graf.adj[v])
        if (!used[i.to]){
            result.push_back({v, i.to, i.weight});
            spanning_dfs_adj(graf, i.to, used, result);
        }
}


pair <vector <span_edge> , int > spanning_tree_adj(graf_adj graf){
    vector <span_edge> result;
    vector <bool> used;
    used.resize(graf.number_vertex);
    spanning_dfs_adj(graf, 0, used, result);
    int weight = 0;
    for (auto i : result)
        weight += i.weight;
    return {result, weight};
}

pair <vector <span_edge> , int > spanning_tree_matrix(graf_matrix graf){
    vector <span_edge> result;
    vector <bool> used;
    used.resize(graf.number_vertex);
    spanning_dfs_matrix(graf, 0, used, result);
    int weight = 0;
    for (auto i : result)
        weight += i.weight;
    return {result, weight};
}

pair <vector <span_edge> , int > minimal_spanning_tree_adj(graf_adj graf){
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

pair <vector <span_edge> , int > minimal_spanning_tree_matrix(graf_matrix graf){
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
    graf_adj graph_adj = graf_adj(n, is_directed == 'y');
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
                graph_adj.add(from, to , w);
            }
            else {
                graph_adj.add(from, to);
            }
            cout << "Done\n";

        }
        if (command == "search_component"){
            vector <vector <int> > result = search_component_adj(graph_adj);
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
            vector <int> dist = bfs_adj(graph_adj, v);
            cout << "Vector of distance from " << v << " to others:\n";
            for (int i = 0; i < dist.size(); ++i){
                cout << "for " <<i << " : " << dist[i] << "\n";
            }
            cout << "\nDone\n";
        }
        if (command == "dijkstra"){
            int v;
            cin >> v;
            vector <int> dist = dijkstra_adj(graph_adj, v);
            cout << "Vector of distance from " << v << " to others:\n";
            for (int i = 0; i < dist.size(); ++i){
                cout << "for " <<i << " : " << dist[i] << "\n";
            }
            cout << "\nDone\n";
        }
        if (command == "top_sort"){
            vector <int> result = topological_sort_adj(graph_adj);
            cout << "Result :\n";
            for (auto i : result)
                cout << i << " ";
            cout << "\nDone\n";
        }
        if (command == "spanning_tree"){
            pair < vector <span_edge>, int> ans = spanning_tree_adj(graph_adj);
            cout << "Weight of tree : " << ans.second << "\n";
            cout << "Tree :\n";
            for (auto i : ans.first){
                cout << "from " << i.from << " to " << i.to << " weight is " << i.weight << "\n";
            }
            cout << "Done\n";
        }
        if (command == "min_spanning_tree"){
            pair < vector <span_edge>, int> ans = minimal_spanning_tree_adj(graph_adj);
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
    graf_matrix graph_matrix = graf_matrix(n, is_directed == 'y');
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
                graph_matrix.add(from, to , w);
            }
            else {
                graph_matrix.add(from, to);
            }
            cout << "Done\n";

        }
        if (command == "search_component"){
            vector <vector <int> > result = search_component_matrix(graph_matrix);
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
            vector <int> dist = bfs_matrix(graph_matrix, v);
            cout << "Vector of distance from " << v << " to others:\n";
            for (int i = 0; i < dist.size(); ++i){
                cout << "for " <<i << " : " << dist[i] << "\n";
            }
            cout << "\nDone\n";
        }
        if (command == "dijkstra"){
            int v;
            cin >> v;
            vector <int> dist = dijkstra_matrix(graph_matrix, v);
            cout << "Vector of distance from " << v << " to others:\n";
            for (int i = 0; i < dist.size(); ++i){
                cout << "for " <<i << " : " << dist[i] << "\n";
            }
            cout << "\nDone\n";
        }
        if (command == "top_sort"){
            vector <int> result = topological_sort_matrix(graph_matrix);
            cout << "Result :\n";
            for (auto i : result)
                cout << i << " ";
            cout << "\nDone\n";
        }
        if (command == "spanning_tree"){
            pair < vector <span_edge>, int> ans = spanning_tree_matrix(graph_matrix);
            cout << "Weight of tree : " << ans.second << "\n";
            cout << "Tree :\n";
            for (auto i : ans.first){
                cout << "from " << i.from << " to " << i.to << " weight is " << i.weight << "\n";
            }
            cout << "Done\n";
        }
        if (command == "min_spanning_tree"){
            pair < vector <span_edge>, int> ans = minimal_spanning_tree_matrix(graph_matrix);
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
            graf_adj adj; adj.graf_random(n, m);
            graf_matrix matrix; matrix.graf_random(n, m);
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
        }
    }
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
    int n;
    cin >> n;
    graf_matrix graf = graf_matrix(n, 0);
    int m;
    cin >> m;
    for (int i = 0; i < m; ++i){
        int a, b, w;
        cin >> a >> b >> w;
        graf.add(a, b, w);
    }
    vector <span_edge> ans = minimal_spanning_tree_matrix(graf).first;
    for (auto i : ans){
        cout << i.from << " " << i.to << " " << i.weight << "\n";
    }
    return 0;
}
