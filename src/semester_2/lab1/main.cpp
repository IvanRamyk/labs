#include <bits/stdc++.h>

using std::vector;
using std::string;
using std::cout;

struct Album {
    std::string name;
    std::string artist;
    int year;
    Album()= default;
};

void print_album(Album * album) {
    cout << album->name << " | " << album->artist << " | " << album->year << "\n";
};

void print_albums(std::vector <Album *> albums){
    for (auto i : albums)
        print_album(i);
}

int rand_num(int max) {
    static std::random_device rd;
    static std::seed_seq seed { rd(), static_cast<unsigned int>(time(nullptr))};
    static std::mt19937_64 gen(seed);
    std::uniform_real_distribution<double> dist(0, max);

    return int(dist(gen));
}

const long long MOD = 1e9 + 7;
const long long COEF = 57;

struct Node {
    long long m;
    long long a;
    long long b;
    vector<Album*> albums;
    vector<Album*> hash_album;
};

vector<Album *> get_albums(const string& route){
    std::ifstream input;
    input.open(route);
    vector <Album *> result;
    while (!input.eof()){
        auto album = new Album;
        getline(input, album->name);
        getline(input, album->artist);
        string temp;
        getline(input, temp);
        album->year=  atoi(temp.c_str());
        result.push_back(album);
    }
    return result;
}

long long hash_album_name(string name, int count, int a = COEF, int b = 0, int mod = MOD) {
    long long hash = b;
    long long length = name.length();
    for(int i = 0; i < length; i++) {
        hash = (hash + ((int) name[i])*a + b) % mod;
    }
    return hash % count;
}

void create_inside_hash(Node* h) {
    h->m = h->albums.size()*h->albums.size();
    h->hash_album.resize(h->m);
    if(h->albums.size() == 1) {
        h->a = 0;
        h->b = 0;
        h->hash_album[0] = h->albums[0];
        return;
    }
    bool check_collissions = false;
    while(!check_collissions) {
        bool collissions[h->m];
        for(int i = 0; i < h->m; i++) {
            collissions[i] = false;
        }

        h->a = rand_num( MOD - 2) + 1;
        h->b = rand_num( MOD - 1);
        check_collissions = true;
        for(auto album:h->albums) {
            int hash = hash_album_name(album->name, h->m, h->a, h->b);
            if(collissions[hash]) {
                check_collissions = false;
                break;
            } else {
                h->hash_album[hash] = album;
                collissions[hash] = true;
            }
        }
    }
    h->albums.clear();
}

vector<Node*> create_hash(const vector<Album *> &albums) {
    vector<Node*> hash(albums.size());
    for(int i = 0; i < albums.size(); i++)
        hash[i] = new Node();
    for(auto album:albums)
        hash[hash_album_name(album->name, albums.size())]->albums.push_back(album);
    for(auto h:hash)
        if(h->albums.size() > 0)
            create_inside_hash(h);
    return hash;
}

Album* get_album_by_name(vector<Node*> hash, const string &name) {
    int value = hash_album_name(name, hash.size());
    Node* h = hash[value];
    if(h->hash_album.size() == 0)
        return nullptr;

    value = hash_album_name(name, h->m, h->a, h->b);
    if(value < h->hash_album.size()) {
        Album *res = h->hash_album[value];
        if (res->name == name)
            return res;
    }
    return nullptr;
}

void queries(vector <Node *> table) {
    while (true) {
        string command;
        getline(std::cin, command);
        if (command == "exit")
            break;
        if (command == "search") {
            string album_name;
            getline(std::cin, album_name);
            Album * result = get_album_by_name(table, album_name);
            if (result == nullptr)
                cout << "None\n";
            else
                print_album(result);
        }
    }
}


int main() {
    vector <Album *> albums = get_albums("../data");
    print_albums(albums);
    vector <Node *> table = create_hash(albums);
    queries(table);
    return 0;
}
