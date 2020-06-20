#include <iostream>
#include <vector>
#include <fstream>
#include <gtest/gtest.h>
#include <queue>

template <typename T>
struct BinomialNode {
    T key;
    BinomialNode<T> * parent;
    BinomialNode<T> * child;
    BinomialNode<T> * sibling;
    int degree;
    BinomialNode()= default;
    BinomialNode(T _key, BinomialNode<T> * _parent = nullptr, BinomialNode<T> * _child = nullptr,
                 BinomialNode<T> * _sibling = nullptr, int _degree = 0):
            parent(_parent), key(_key), child(_child), sibling(_sibling), degree(_degree){}
};

template <typename T>
class BinomialHeap {
private:
    BinomialNode<T> * head;
public:
    BinomialHeap() {
        head = nullptr;
    }
    BinomialNode<T> * extract_minimum() {
        auto node = head;
        if (node == nullptr)
            return node;
        auto cur = node;
        while (cur != nullptr) {
            if (cur->key < node->key)
                node = cur;
            cur = cur->sibling;
        }
        return node;
    }

    void link(BinomialNode<T> * a, BinomialNode<T> * b){
        a->parent = b;
        a->sibling = b->child;
        b->child = a;
        b->degree++;
    }

    BinomialNode<T> * merge(BinomialNode<T> * a, BinomialNode<T> * other){
        BinomialNode<T> * new_head = nullptr;
        BinomialNode<T> * H = nullptr;
        auto head1 = a;
        auto head2 = other;
        while (head1 != nullptr || head2 != nullptr) {
            if (head1 == nullptr ||( (head2 != nullptr)  && (head2->degree < head1->degree))) {
                if (new_head == nullptr) {
                    new_head = head2;
                    H = new_head;
                }
                else {
                    new_head->sibling = head2;
                    new_head = new_head->sibling;
                }
                head2 = head2->sibling;
            }
            else {
                if (new_head == nullptr) {
                    new_head = head1;
                    H = new_head;
                }
                else {
                    new_head->sibling = head1;
                    new_head = new_head->sibling;
                }
                head1 = head1->sibling;
            }
        }
        return H;
    }

    BinomialNode<T> * _union(BinomialNode<T> * a, BinomialNode<T> * b){
        BinomialNode<T> * n_head = merge(a, b);
        if (n_head == nullptr)
            return nullptr;
        BinomialNode<T> * prev = nullptr;
        BinomialNode<T> * cur = n_head;
        BinomialNode<T> * next = cur->sibling;
        while (next != nullptr) {
            if (cur->degree != next->degree || (next->sibling != nullptr && next->degree == next->sibling->degree)) {
                prev = cur;
                cur = next;
            } else if (cur->key <= next->key) {
                cur->sibling = next->sibling;
                link(next, cur);
            } else {
                if (prev == nullptr) {
                    n_head = next;
                } else {
                    prev->sibling = next;
                }
                link(cur, next);
                next = cur;
            }
            next = next->sibling;
        }
        return n_head;
    }

    void insert(T key) {
        auto node = new BinomialNode<T>(key);
        head = _union(head, node);
        //std::cout << "after insertion " << head->degree << "\n";
    }

    void print(BinomialNode<T> * node) {
        std::cout << "node " << node->key << "\n";
        if (node->child != nullptr) {
            std::cout << "go to child " << node->child->key << "\n";
            print(node->child);
        }
        if (node->sibling != nullptr) {
            std::cout << "go to sibling " << node->sibling->key << "\n";
            print(node->sibling);
        }
    }

    void print_() {
        auto cur = head;
        while (cur != nullptr){
            std::cout << "New B-tree\n";
            print(cur);
            cur = cur->sibling;
        }
    }

    BinomialNode<T> *  reverse(BinomialNode<T> * cur) {
        cur->parent = nullptr;
        BinomialNode<T> * prev = nullptr;
        while (cur != nullptr) {
            auto temp = cur->sibling;
            cur->sibling = prev;
            prev = cur;
            cur = temp;
        }
        return prev;
    }

    void pop(){
        auto * node = extract_minimum();
        if (node == nullptr)
            return;
        BinomialNode<T> * prev = nullptr;
        auto * cur = head;
        while (cur != node) {
            prev = cur;
            cur = cur->sibling;
        }
        if (prev == nullptr)
            head = cur->sibling;
        else {
            prev->sibling = cur->sibling;
        }
        if (node->child == nullptr)
            return;
        auto head1 = reverse(node->child);
        head = _union(head, head1);
        delete node;
    }

    bool decrease_key(BinomialNode<T> * node, T k) {
        if (node->key < k)
            return false;
        node->key = k;
        while (node->parent != nullptr && node->parent->key > k)  {
            T temp = node->key;
            node->key = node->parent->key;
            node->parent->key = temp;
            node = node->parent;
        }
    }
};


void int_interaction() {
    BinomialHeap<int> heap;
    while (true){
        std::string command;
        getline(std::cin, command);
        if (command == "exit")
            break;
        if (command == "insert") {
            int v;
            std::cin >> v;
            heap.insert(v);
            std::cout << "ok\n";
        }
        if (command == "pop") {
            heap.pop();
            std::cout << "ok\n";
        }
        if (command == "min") {
            auto * ans = heap.extract_minimum();
            if (ans != nullptr)
                std::cout << ans->key << "\n";
        }
    }
}


TEST(Heap, test){
    BinomialHeap<int> heap;
    for (int i = 100; i > 0; --i)
        heap.insert(i);
    for (int i = 1000; i < 2000; ++i)
        heap.insert(i);
    for (int i = 1; i <= 100; ++i){
        EXPECT_EQ(heap.extract_minimum()->key, i);
        heap.pop();
    }
    for (int i = 1000; i < 2000; ++i) {
        EXPECT_EQ(heap.extract_minimum()->key, i);
        heap.pop();
    }
}

TEST(Heap, rand_test){
    srand(time(0));
    BinomialHeap<int> heap;
    std::priority_queue<int> q;
    for (int i = 0; i < 100; i++) {
        int v = rand() % 10000;
        heap.insert(v);
        q.push(-v);
    }
    for (int i = 0; i < 10000; ++i){
        if (rand() % 2 == 1)  {
            EXPECT_EQ(heap.extract_minimum()->key, -q.top());
            heap.pop();
            q.pop();
        }
        else {
            int v= rand() % 10000;
            heap.insert(v);
            q.push(-v);
        }
    }
}


struct Album {
    std::string name;
    std::string artist;
    int year;
    Album()= default;
    Album(std::string _name, std::string _artist, int _year):
            name(std::move(_name)), year(_year), artist(std::move(_artist)) {}
    bool operator <(Album b) { return this->name < b.name; }
    bool operator !=(Album b) { return this->name != b.name; }
    bool operator <=(Album b) { return this->name <= b.name; }
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
    BinomialHeap<Album> heap;
    while (true) {
        std::string command;
        getline(std::cin, command);
        if (command == "exit")
            break;
        if (command == "import data")  {
            auto data = get_albums("../data");
            for (auto album: data)
                heap.insert(album);
            std::cout << "ok\n";
            continue;
        }
        if (command == "insert") {
            heap.insert(get_album());
            std::cout << "ok\n";
            continue;
        }
        if (command == "pop") {
            heap.pop();
            std::cout << "ok\n";
            continue;
        }
        if (command == "min") {
            auto * ans = heap.extract_minimum();
            if (ans != nullptr)
                print_album(ans->key);
            continue;
        }
        std::cout << "Try again\n";
    }
}


int main() {
    testing::InitGoogleTest();
    RUN_ALL_TESTS();
    queries();

    return 0;
}
