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
    cout << "Graph with " << number_vertex << " vertexes\nVertexes = {";
    for (int i = 0; i <vertexes.size() - 1; ++i)
        cout << vertexes[i] << ", ";
    cout << *(vertexes.end() - 1) << "};\n";
    cout << "Edges = { \n";
    for (int i = 0; i < number_vertex; ++i){
        for (auto j : adj[i])
            if (directed  || (i  < j.to))
                cout << "\t(" << vertexes[i] << ", " << vertexes[j.to] << ") - " << j.data  << ";\n";
    }
    cout << "}.\n";
}

template<typename VertexT, typename EdgeT>
int Graph<VertexT, EdgeT>::position(VertexT v) {
    for (int i = 0; i < vertexes.size(); ++i)
        if (vertexes[i] == v) return i;
    return -1;
}


template<typename VertexT, typename EdgeT>
bool Graph<VertexT, EdgeT>::addEdge(VertexT from, VertexT to, EdgeT edge) {
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
void Graph<VertexT, EdgeT>::addVertex(VertexT v) {
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
vector<vector<VertexT>> Graph<VertexT, EdgeT>::searchComponent() {
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
bool Graph<VertexT, EdgeT>::topDfs(int v, std::vector<int> &used, vector<VertexT> &ans) {
    used[v] = 1;
    bool result = 1;
    for (auto i : adj[v]) {
        if (!used[i.to]) {
            result = result  & topDfs(i.to, used, ans);
        }
        else if (used[i.to] == 1) return 0;
    }
    used[v] = 2;
    ans.push_back(vertexes[v]);
    return result;
}

template <typename VertexT, typename  EdgeT>
std::pair<bool, vector <VertexT>> Graph<VertexT, EdgeT>::topologicalSort() {
    int n = this->number_vertex;
    std::vector <int> used;
    used.resize(n);
    for (int i=0; i<n; ++i)
        used[i] = 0;
    std::vector <VertexT> result;
    bool answer = 1;
    for (int i=0; i<n; ++i)
        if (!used[i])
            answer &= topDfs (i, used, result);
    std::reverse (result.begin(), result.end());
    return {answer, result};
}

template<typename VertexT, typename EdgeT>
Graph<VertexT, EdgeT> Graph<VertexT, EdgeT>::minimumSpanningTree(){
    Graph tree;
    for (int i = 0; i < number_vertex; ++i)
        tree.addVertex(vertexes[i]);
    DisjointSet set(number_vertex);
    vector <SpanningTreeEdge<EdgeT>> edges;
    for (int i = 0; i < number_vertex; ++i)
        for (auto j : adj[i])
            edges.push_back(SpanningTreeEdge<EdgeT>(j.data, i, j.to));
    std::sort(edges.begin(), edges.end(),
              [](const SpanningTreeEdge<EdgeT> &a, const SpanningTreeEdge<EdgeT> &b) {return a.data < b.data;});
    for (auto i : edges)
        if (!set.isSameSet(i.from, i.to)){
            tree.addEdge(vertexes[i.from], vertexes[i.to], i.data);
            set.join(i.from, i.to);
        }
    return tree;
}

template<typename VertexT, typename EdgeT>
int Graph<VertexT, EdgeT>::center() {
    vector<vector<std::pair<bool, EdgeT>>> floyd(number_vertex);
    for (int i = 0; i < number_vertex;++i)
        floyd[i].resize(number_vertex);
    for (int i = 0; i < number_vertex; ++i)
        for (int j = 0; j < number_vertex; ++j)
            if (i == j) {
                floyd[i][j].first = true;
                floyd[i][j].second = EdgeT();
            }
            else {
                floyd[i][j].first = false;
            }
    for (int i = 0; i < number_vertex; ++i)
        for (auto j : adj[i]) {
            floyd[i][j.to] = {true, j.data};
        }
    for (int k=0; k<number_vertex; ++k)
        for (int i=0; i<number_vertex; ++i)
            for (int j=0; j<number_vertex; ++j)
                if (floyd[i][k].first && floyd[k][j].first)
                    if ((floyd[i][j].first == false) || (floyd[i][j].second > floyd[i][k].second  + floyd[k][j].second)) {
                        floyd[i][j].second = floyd[i][k].second + floyd[k][j].second;
                        floyd[i][j].first = true;
                    }
    int v_center = 0;
    EdgeT center = floyd[0][0].second;
    for (int i = 1 ; i < number_vertex; ++i)
        if (center < floyd[0][i].second)
            center = floyd[0][i].second;
    for (int i = 1; i < number_vertex; ++i){
        EdgeT n_center = floyd[i][0].second;
        for (int j = 1; j < number_vertex; ++j)
            if (n_center < floyd[i][j].second)
                n_center = floyd[i][j].second;
        if (n_center < center){
            center = n_center;
            v_center = i;
        }
    }
    return v_center;
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
void Tree<VertexT, EdgeT>::printNode(TreeNode<VertexT, EdgeT> * current_node) {
    if (current_node == nullptr)
        return;
    cout << current_node->data << "\n";
    for (auto i : current_node->children)
        printNode(i);
}

template <typename VertexT, typename EdgeT>
void Tree<VertexT, EdgeT>::print(){
    printNode(root);
}

template <typename VertexT, typename EdgeT>
void Tree<VertexT, EdgeT>::convert(Graph<VertexT, EdgeT> graph, int graph_root) {
    vector <bool> used(graph.number_vertex, false);
    root = dfs(graph, used, graph_root);
}

template <typename VertexT, typename EdgeT>
EdgeT Tree<VertexT, EdgeT>::total(TreeNode<VertexT, EdgeT>  * current_node) {
    EdgeT s = current_node->edge;
    for (auto i : current_node->children)
            s = s + total(i);
    return s;
}

template <typename VertexT, typename EdgeT>
EdgeT Tree<VertexT, EdgeT>::totalWeight() {
    return total(root);
}




#endif //LAB1_GRAPH_HXX
