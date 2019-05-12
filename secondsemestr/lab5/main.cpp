#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

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
            matrix[to][from] = orient;
        ++number_edge;
    }
    void graf_random(int v, int e, int o){
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
    void graf_random(int v, int e, int o){
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

void dfs(graf_adj &graf, int v, vector <bool> &used, vector <int> &component){
    used[v] = 1;
    component.push_back(v);
    for (auto i : graf.adj[v])
        if (!used[i.to]) dfs(graf, i.to, used, component);
}

vector < vector <int> > search_component_adj(graf_adj graf){
    vector <bool> used;
    used.resize(graf.number_vertex);
    vector <vector <int> > result;
    vector <int> component;
    cout << "done\n";
    for (int i = 0; i < graf.number_vertex; ++i)
        if (!used[i]) {
            component.clear();
            dfs(graf, i, used, component);
            result.push_back(component);
        }
    return result;
}

vector <int> bfs(graf_adj graf, int v){
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

vector <int> dijkstra(graf_adj graf, int v){
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

void top_dfs (graf_adj &graf, int v, vector <bool>& used, vector <int> &ans) {
    used[v] = true;
    for (auto i : graf.adj[v]){
        if (!used[i.to]) {
            top_dfs(graf, i.to, used, ans);
        }
    }
    cout << v << "\n";
    ans.push_back(v);
}

vector <int> topological_sort(graf_adj graf) {
    int n = graf.number_vertex;
    vector <bool> used;
    used.resize(n);
    for (int i=0; i<n; ++i)
        used[i] = false;
    vector <int> result;
    for (int i=0; i<n; ++i)
        if (!used[i])
            top_dfs (graf, i, used, result);
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

void spanning_dfs(graf_adj &graf, int v, vector <bool> &used, vector <span_edge> &result){
    used[v] = 1;
    for (auto i : graf.adj[v])
        if (!used[i.to]){
            result.push_back({v, i.to, i.weight});
            spanning_dfs(graf, i.to, used, result);
        }
}

pair <vector <span_edge> , int > spanning_tree(graf_adj graf){
    vector <span_edge> result;
    vector <bool> used;
    used.resize(graf.number_vertex);
    spanning_dfs(graf, 0, used, result);
    int weight = 0;
    for (auto i : result)
        weight += i.weight;
    return {result, weight};
}

pair <vector <span_edge> , int > minimal_spanning_tree(graf_adj graf){
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
        result.push_back(q.top());
        int cur = q.top().to;
        used[cur] = 1;
        q.pop();
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


int main() {
    int n;
    cin >> n;
    graf_adj graf = graf_adj(n, 0);
    int m;
    cin >> m;
    for (int i = 0; i < m; ++i){
        int a, b, w;
        cin >> a >> b >> w;
        graf.add(a, b, w);
    }
    vector <span_edge> ans = minimal_spanning_tree(graf).first;
    for (auto i : ans){
        cout << i.from << " " << i.to << " " << i.weight << "\n";
    }
    return 0;
}
