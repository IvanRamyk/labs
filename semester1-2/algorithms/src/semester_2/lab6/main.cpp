//
// Created by Ivan Ramyk on 3/21/20.
//
#include "tests/test.hpp"
#include "BPlusTree.hpp"


struct Album {
    std::string name;
    std::string artist;
    int year;
    Album()= default;
    Album(std::string _name, std::string _artist, int _year):
            name(std::move(_name)), year(_year), artist(std::move(_artist)) {}
};

bool operator <(Album const &a, Album const &b) { return a.name < b.name; }
bool operator !=(Album const &a, Album const &b) { return a.name != b.name; }

void print_album(Album album) {
    std::cout << album.name << " | " << album.artist << " | " << album.year << "\n";
};

void print_albums(std::vector <Album> albums){
    for (auto i : albums)
        print_album(i);
}


Album get_album(int &key){
    Album album;
    std::string buff;
    getline(std::cin, buff);
    key = atoi(buff.c_str());
    getline(std::cin, album.name);
    getline(std::cin, album.artist);
    std::string temp;
    getline(std::cin, temp);
    album.year=  atoi(temp.c_str());
    return album;
}

std::vector<std::pair<int, Album>> get_albums(const std::string& route){
    std::ifstream input;
    input.open(route);
    std::vector <std::pair<int, Album >> result;
    while (!input.eof()){
        int key;
        Album album;
        std::string buff;
        getline(input, buff);
        key = atoi(buff.c_str());
        getline(input, album.name);
        getline(input, album.artist);
        std::string temp;
        getline(input, temp);
        album.year=  atoi(temp.c_str());
        result.push_back({key,album});
    }
    input.close();
    return result;
}



std::map<Album, int> keys;

void queries() {
    int n;
    std::cout << "Введіть мінімальну степнінь дерева\n";
    std::cin >> n;
    BPlusTree<Album> tree(n);

    std::string temp;

    getline(std::cin, temp);
    while (true) {
        std::string command;
        getline(std::cin, command);
        if (command == "exit")
            break;
        if (command == "import data")  {
            auto data = get_albums("../data");
            for (auto album: data) {
                keys[album.second] = album.first;
                tree.insert(album.first, std::make_shared<Album>(album.second));
            }
            std::cout << "ok\n";
            continue;
        }
        if (command == "insert") {
            int key;
            auto alb = get_album(key);
            keys[alb] = key;
            tree.insert(key, std::make_shared<Album>(alb));
            std::cout << "ok\n";
            continue;
        }
        if (command == "print") {
            for (auto it = tree.begin(); it != tree.end(); ++it)
                print_album(*it);
            continue;
        }
        if (command == "search") {
            Album album;
            getline(std::cin, album.name);
            if (keys.count(album)){
                auto node = tree.search(keys[album]);
                if (node != nullptr)
                    print_album(*node);
                else
                    std::cout << "None\n";
                continue;
            }
            std::cout << "None\n";
        }
        if (command == "remove") {
            Album album;
            getline(std::cin, album.name);

            if (keys.count(album)) {
                tree.remove(keys[album]);
                std::cout << "ok\n";
                continue;
            }
        }
        std::cout << "Try again\n";
    }
}

int main(){
    testAll();
    queries();
    return 0;
}
