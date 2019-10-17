//
// Created by Ivan Ramyk on 10/16/19.
//

#ifndef LAB1_GRAPH_HXX
#define LAB1_GRAPH_HXX


template<typename VertexT, typename EdgeT>
Graph<VertexT, EdgeT>::Graph(bool is_directed) {
    directed = is_directed;
    number_vertex = 0;
}

template<typename VertexT, typename EdgeT>
void Graph<VertexT, EdgeT>::print(){
    cout << "Graph with " << number_vertex << " vertexes\n";
    for (int i = 0; i < number_vertex; ++i){
        for (auto j : adj[i])
            if (directed  || (i  < j.to))
                cout << "Edge (" << vertexes[i] << ", " << vertexes[j.to] << ") - " << j.data  << "\n";
    }
}

template<typename VertexT, typename EdgeT>
int Graph<VertexT, EdgeT>::position(VertexT v) {
    for (int i = 0; i < vertexes.size(); ++i)
        if (vertexes[i] == v) return i;
    return -1;
}


template<typename VertexT, typename EdgeT>
bool Graph<VertexT, EdgeT>::add_edge(VertexT from, VertexT to, EdgeT edge) {
    int from_pos = position(from);
    int to_pos = position(to);
    if (from_pos == -1 || to_pos == -1){
        cout << "Invalid vertexes!\n";
        return false;
    }
    Edge<EdgeT> edge_from(edge, to_pos);
    adj[from_pos].push_back(edge_from);
    if (!directed){
        Edge<EdgeT> edge_to(edge, from_pos);
        adj[to_pos].push_back(edge_to);
    }
    return true;
}

template <typename  VertexT, typename EdgeT>
void Graph<VertexT, EdgeT>::add_vertex(VertexT v) {
    vertexes.push_back(v);
    ++number_vertex;
    adj.push_back({});
}

template <typename  VertexT, typename EdgeT>
void Graph<VertexT, EdgeT>::dfs(int v, std::vector<bool> &used, std::vector<VertexT> &component) {
    used[v] = true;
    component.push_back(vertexes[v]);
    for (auto i : this->adj[v])
        if (!used[i.to]) dfs(i.to, used, component);
}

template <typename  VertexT, typename EdgeT>
vector<vector<VertexT>> Graph<VertexT, EdgeT>::search_component() {
    vector <bool> used;
    used.resize(this->number_vertex);
    vector <std::vector <VertexT> > result;
    vector <VertexT> component;
    for (int i = 0; i < this->number_vertex; ++i)
        if (!used[i]) {
            component.clear();
            dfs(i, used, component);
            result.push_back(component);
        }
    return result;
}

template  <typename VertexT, typename  EdgeT>
std::vector <pair<int, VertexT>> Graph <VertexT, EdgeT>::bfs(VertexT V)
{   int v = position(V);
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
    vector <pair<int, VertexT>> answer;
    for (int i = 0; i < dist.size(); ++i)
        answer.push_back({dist[i], vertexes[i]});
    return answer;
}

template  <typename VertexT, typename  EdgeT>
int Graph <VertexT, EdgeT>::bfs(VertexT V1, VertexT V2)
{   int v = position(V1);
    int to = position(V2);
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
    return dist[to];
}


template <typename VertexT, typename  EdgeT>
bool Graph<VertexT, EdgeT>::top_dfs(int v, std::vector<int> &used, vector<VertexT> &ans) {
    used[v] = 1;
    bool result = 1;
    for (auto i : adj[v]) {
        if (!used[i.to]) {
            result = result  & top_dfs(i.to, used, ans);
        }
        else if (used[i.to] == 1) return 0;
    }
    used[v] = 2;
    ans.push_back(vertexes[v]);
    return result;
}

template <typename VertexT, typename  EdgeT>
std::pair<bool, vector <VertexT>> Graph<VertexT, EdgeT>::topological_sort() {
    int n = this->number_vertex;
    std::vector <int> used;
    used.resize(n);
    for (int i=0; i<n; ++i)
        used[i] = 0;
    std::vector <VertexT> result;
    bool answer = 1;
    for (int i=0; i<n; ++i)
        if (!used[i])
            answer &= top_dfs (i, used, result);
    std::reverse (result.begin(), result.end());
    return {answer, result};
}

template<typename VertexT, typename EdgeT>
Graph<VertexT, EdgeT> Graph<VertexT, EdgeT>::minimum_spanning_tree(){
    Graph tree;
    for (int i = 0; i < number_vertex; ++i)
        tree.add_vertex(vertexes[i]);
    DisjointSet set(number_vertex);
    vector <SpanningTreeEdge<EdgeT>> edges;
    for (int i = 0; i < number_vertex; ++i)
        for (auto j : adj[i])
            edges.push_back(SpanningTreeEdge<EdgeT>(j.data, i, j.to));
    std::sort(edges.begin(), edges.end(),
              [](const SpanningTreeEdge<EdgeT> &a, const SpanningTreeEdge<EdgeT> &b) {return a.data < b.data;});
    for (auto i : edges)
        if (!set.same_set(i.from, i.to)){
            tree.add_edge(vertexes[i.from], vertexes[i.to], i.data);
            set.join(i.from, i.to);
        }
    return tree;
}

template<typename VertexT, typename EdgeT>
Tree<VertexT, EdgeT>::Tree() = default;

template <typename VertexT, typename EdgeT>
TreeNode<VertexT, EdgeT> * Tree<VertexT, EdgeT>::dfs(Graph<VertexT, EdgeT> &graph, vector <bool> &used, int v, EdgeT edge){
    used[v] = true;
    auto * current_node = new TreeNode<VertexT, EdgeT>(graph.vertexes[v], edge);
    for (auto i : graph.adj[v])
        if (!used[i.to]){
            auto * child = dfs(graph, used, i.to, i.data);
            current_node->children.push_back(child);
        }
    return current_node;
}

template <typename VertexT, typename EdgeT>
void Tree<VertexT, EdgeT>::print_node(TreeNode<VertexT, EdgeT> * current_node) {
    if (current_node == nullptr)
        return;
    cout << current_node->data << "\n";
    for (auto i : current_node->children)
        print_node(i);
}

template <typename VertexT, typename EdgeT>
void Tree<VertexT, EdgeT>::print(){
    print_node(root);
}

template <typename VertexT, typename EdgeT>
void Tree<VertexT, EdgeT>::convert(Graph<VertexT, EdgeT> graph, int graph_root) {
    vector <bool> used(graph.number_vertex, false);
    root = dfs(graph, used, graph_root);
}

#endif //LAB1_GRAPH_HXX
