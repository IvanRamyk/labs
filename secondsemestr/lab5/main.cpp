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
        orient = 0;
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

int n; // число вершин
vector<int> g[MAXN]; // граф
bool used[MAXN];
vector<int> ans;

void dfs (int v) {
    used[v] = true;
    for (size_t i=0; i<g[v].size(); ++i) {
        int to = g[v][i];
        if (!used[to])
            dfs (to);
    }
    ans.push_back (v);
}

void topological_sort() {
    for (int i=0; i<n; ++i)
        used[i] = false;
    ans.clear();
    for (int i=0; i<n; ++i)
        if (!used[i])
            dfs (i);
    reverse (ans.begin(), ans.end());
}

int main() {
    int n;
    cin >> n;
    graf_adj graf = graf_adj(n);
    int m;
    cin >> m;
    for (int i = 0; i < m; ++i){
        int a, b;
        cin >> a >> b;
        graf.add(a, b);
    }
    int v;
    cin >> v;
    vector <int> dist = bfs(graf, v);
    for (auto i : dist){
        cout << i << " ";
    }
    return 0;
}
