//
// Created by Ivan Ramyk on 3/21/20.
//
#include "tests/test.hpp"

struct Album {
    std::string name;
    std::string artist;
    int year;
    Album()= default;
    Album(std::string _name, std::string _artist, int _year):
            name(std::move(_name)), year(_year), artist(std::move(_artist)) {}
    bool operator <(Album b) { return this->name < b.name; }
    bool operator !=(Album b) { return this->name != b.name; }
};

void print_album(Album album) {
    std::cout << album.name << " | " << album.artist << " | " << album.year << "\n";
};

void print_albums(std::vector <Album> albums){
    for (auto i : albums)
        print_album(i);
}

std::vector<Album> get_albums(const std::string& route){
    std::ifstream input;
    input.open(route);
    std::vector <Album > result;
    while (!input.eof()){
        Album album;
        getline(input, album.name);
        getline(input, album.artist);
        std::string temp;
        getline(input, temp);
        album.year=  atoi(temp.c_str());
        result.push_back(album);
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

void queries() {
    RedBlackTree<Album> tree;
    while (true) {
        std::string command;
        getline(std::cin, command);
        if (command == "exit")
            break;
        if (command == "import data")  {
            auto data = get_albums("../data");
            for (auto album: data)
                tree.insert(album);
            std::cout << "ok\n";
            tree.updateSize();
            continue;
        }
        if (command == "insert") {
            tree.insert(get_album());
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
            auto node = tree.search(album);
            if (node != nullptr)
                print_album(node->value());
            else
                std::cout << "None\n";
            continue;
        }
        if (command == "remove") {
            Album album;
            getline(std::cin, album.name);
            tree.remove(tree.search(album));
            std::cout << "ok\n";
            continue;
        }
        if (command == "select") {
            std::string buff;
            getline(std::cin, buff);
            int k = atoi(buff.c_str());
            //tree.updateSize();
            auto node = tree.select(k);
            if (node != nullptr)
                print_album(node->value());
            else
                std::cout << "None\n";
            continue;
        }
        if (command == "order") {
            Album album;
            getline(std::cin, album.name);
            auto node = tree.search(album);
            if (node != nullptr)
                std::cout << tree.order(node) << "\n";
            else
                std::cout << "None\n";
            continue;
        }
        std::cout << "Try again\n";
    }
}

int main(){
    testAll();
    queries();
    return 0;
}
