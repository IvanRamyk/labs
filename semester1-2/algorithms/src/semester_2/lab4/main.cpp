#include <bits/stdc++.h>

struct Album {
    std::string name;
    std::string artist;
    int year;
    Album()= default;
    Album(std::string _name, std::string _artist, int _year):
            name(std::move(_name)), year(_year), artist(std::move(_artist)) {}
    bool operator <(Album b) { return this->name < b.name; }
    bool operator !=(Album b) { return this->name != b.name; }
    bool operator ==(Album b) { return this->name == b.name; }
    friend std::ostream& operator<<(std::ostream& os, Album album) {
        os << album.name << " | " << album.artist << " | " << album.year;
        return os;
    }
};
bool operator <(Album a, Album b) { return a.name < b.name; }

void print_album(Album album) {
    std::cout << album.name << " | " << album.artist << " | " << album.year << "\n";
};

void print_albums(std::vector <Album> albums){
    for (auto i : albums)
        print_album(i);
}

std::vector<std::pair<Album, int>> get_albums(const std::string& route){
    std::ifstream input;
    input.open(route);
    std::vector<std::pair<Album, int>> result;
    while (!input.eof()){
        Album album;
        getline(input, album.name);
        getline(input, album.artist);
        std::string temp;
        getline(input, temp);
        album.year=  atoi(temp.c_str());
        getline(input, temp);
        int fre =  atoi(temp.c_str());
        result.push_back({album, fre});
    }
    input.close();
    return result;
}

Album get_album(){
    Album album;
    getline(std::cin, album.name);
    getline(std::cin, album.artist);
    std::string temp;
    getline(std::cin, temp);
    album.year=  atoi(temp.c_str());
    return album;
}

template <typename  T>
struct Node {
    T data;
    Node* left;
    Node* right;
    Node(T _album, Node * _left = nullptr, Node * _right = nullptr): data(_album), left(_left), right(_right) {}
    void print() {
        std::cout << "data: " << data << "\n";
        if (left != nullptr) {
            std::cout << "Go left\n";
            left->print();
        }
        if (right != nullptr) {
            std::cout << "Go right\n";
            right->print();
        }
    }
};

int sum(int l, int r, std::vector <int> &pre){
    if (l > r)
        return 0;
    if (l == 0)
        return pre[r];
    return pre[r] - pre[l - 1];
}

template <typename T>
Node<T> * buildTree(std::vector <std::pair<T, int>> &data, int l, int r, std::vector<std::vector<int>> &parent) {
    if (l > r)
        return nullptr;
    if (l == r)
        return new Node<T>(data[l].first);
    int m = parent[l][r-  l + 1];
    return new Node<T>(data[m].first, buildTree(data, l,m - 1, parent), buildTree(data, m + 1, r, parent));
}

template<typename T>
Node<T> * optimalBinaryTree(std::vector <std::pair<T, int>> &albums) {
    std::sort(albums.begin(), albums.end());
    int n = albums.size();
    std::vector <std::vector<int>> dp;
    dp.resize(n);
    for (auto &i : dp)
        i.resize(n + 1);
    std::vector <std::vector<int>> parent = dp;
    std::vector <int> pre_sum(n);
    pre_sum[0] = albums[0].second;
    for (int i = 1; i < n; ++i)
        pre_sum[i] = pre_sum[i - 1] + albums[i].second;
    int inf = INT_MAX;
    for (int j = 1; j <= n; ++j)
        for (int i = 0 ; i < n; ++i){
            if (i + j > n)
                continue;
            if (j == 1) {
                dp[i][j] = 0;
            }
            else  {
                int l = i;
                int r = i + j - 1;
                dp[i][j] = dp[l][1] + sum(l + 1, r, pre_sum) + dp[l + 1][r - l];
                parent[i][j] = l;
                if (dp[r][1] + sum(l, r - 1, pre_sum) + dp[l][r - l] < dp[i][j]) {
                    dp[i][j] = dp[r][1] + sum(l, r - 1, pre_sum) + dp[l][r - l];
                    parent[i][j] = r;
                }
                for (int m = l + 1; m < r; ++m) {
                    if (dp[i][j] > sum(l, m - 1, pre_sum) + sum(m + 1, r, pre_sum) + dp[l][m - l] + dp[m + 1][r -  m]){
                        dp[i][j] = sum(l, m - 1, pre_sum) + sum(m + 1, r, pre_sum) + dp[l][m - l] + dp[m + 1][r -  m];
                        parent[i][j] = m;
                    }
                }
            }
        }/*
    for (int i = 0; i < n; ++i)
        for (int j = 1; j <= n; ++j) {
           std::cout << i << " " << j << " " << dp[i][j] << " " <<  parent[i][j] << "\n";
        }*/
    std::cout << dp[0][n] << "\n";
    return buildTree(albums, 0, n - 1, parent);
}

void int_solve() {
    int n;
    //std::freopen("data", "r", stdin);
    int t;
    std::cout << "Print count of int tests\n";
    std::cin >> t;
    while(t--) {
        std::cin >> n;
        std::vector<std::pair<int, int>> v;
        for (int i = 0; i < n; ++i) {
            int temp;
            std::cin >> temp;
            v.push_back({i, temp});
        }
        auto t = optimalBinaryTree(v);
        t->print();
    }
}

void album_solve() {
    std::string route = "../data";
    std::vector <std::pair<Album, int>> data = get_albums(route);
    auto t = optimalBinaryTree(data);
    t->print();
}

int main() {
    int_solve();
    album_solve();
    return 0;
}