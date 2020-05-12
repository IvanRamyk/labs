#include <iostream>
#include <vector>
#include <fstream>
#include <gtest/gtest.h>
#include <queue>
#include <cmath>


using std::cout;
using std::cin;
using std::endl;

const std::string min_str = "";


struct Album {
    std::string name;
    std::string artist;
    int year;

    Album() = default;

    Album(std::string _name, std::string _artist, int _year) :
            name(std::move(_name)), year(_year), artist(std::move(_artist)) {}

    bool operator<(Album b) { return this->name < b.name; }

    bool operator!=(Album b) { return this->name != b.name; }

    bool operator<=(Album b) { return this->name <= b.name; }

    bool operator==(Album b) { return this->name == b.name; }
};

void print_album(Album album) {
    std::cout << album.name << " | " << album.artist << " | " << album.year << "\n";
};

void print_albums(std::vector<Album> albums) {
    for (auto i : albums)
        print_album(i);
}

std::vector<Album> get_albums(const std::string &route) {
    std::ifstream input;
    input.open(route);
    std::vector<Album> result;
    while (!input.eof()) {
        Album album;
        getline(input, album.name);
        getline(input, album.artist);
        std::string temp;
        getline(input, temp);
        album.year = atoi(temp.c_str());
        result.push_back(album);
    }
    input.close();
    return result;
}

Album get_album() {
    Album album;
    getline(std::cin, album.name);
    getline(std::cin, album.artist);
    std::string temp;
    getline(std::cin, temp);
    album.year = atoi(temp.c_str());
    return album;
}

struct node {
    node *parent;
    node *child;
    node *left;
    node *right;
    Album key;
    int degree;
    char mark; // Black or white mark of the node
    char c;
};

struct node *mini = nullptr;


int no_of_nodes = 0;


void insertion(Album val) {
    struct node *new_node = new node;
    new_node->key = val;
    new_node->degree = 0;
    new_node->mark = 'W';
    new_node->c = 'N';
    new_node->parent = nullptr;
    new_node->child = nullptr;
    new_node->left = new_node;
    new_node->right = new_node;
    if (mini != nullptr) {
        (mini->left)->right = new_node;
        new_node->right = mini;
        new_node->left = mini->left;
        mini->left = new_node;
        if (new_node->key < mini->key)
            mini = new_node;
    } else {
        mini = new_node;
    }
    no_of_nodes++;
}

void Fibonnaci_link(struct node *ptr2, struct node *ptr1) {
    (ptr2->left)->right = ptr2->right;
    (ptr2->right)->left = ptr2->left;
    if (ptr1->right == ptr1)
        mini = ptr1;
    ptr2->left = ptr2;
    ptr2->right = ptr2;
    ptr2->parent = ptr1;
    if (ptr1->child == nullptr)
        ptr1->child = ptr2;
    ptr2->right = ptr1->child;
    ptr2->left = (ptr1->child)->left;
    ((ptr1->child)->left)->right = ptr2;
    (ptr1->child)->left = ptr2;
    if (ptr2->key < (ptr1->child)->key)
        ptr1->child = ptr2;
    ptr1->degree++;
}

void Consolidate() {
    int temp1;
    double temp2 = (std::log(no_of_nodes)) / (std::log(2));
    int temp3 = int(temp2);
    struct node *arr[temp3];
    for (int i = 0; i <= temp3; i++)
        arr[i] = nullptr;
    node *ptr1 = mini;
    node *ptr2;
    node *ptr3;
    node *ptr4 = ptr1;
    do {
        ptr4 = ptr4->right;
        temp1 = ptr1->degree;
        while (arr[temp1] != nullptr) {
            ptr2 = arr[temp1];
            if (ptr2->key < ptr1->key) {
                ptr3 = ptr1;
                ptr1 = ptr2;
                ptr2 = ptr3;
            }
            if (ptr2 == mini)
                mini = ptr1;
            Fibonnaci_link(ptr2, ptr1);
            if (ptr1->right == ptr1)
                mini = ptr1;
            arr[temp1] = nullptr;
            temp1++;
        }
        arr[temp1] = ptr1;
        ptr1 = ptr1->right;
    } while (ptr1 != mini);
    mini = nullptr;
    for (int j = 0; j <= temp3; j++) {
        if (arr[j] != nullptr) {
            arr[j]->left = arr[j];
            arr[j]->right = arr[j];
            if (mini != nullptr) {
                (mini->left)->right = arr[j];
                arr[j]->right = mini;
                arr[j]->left = mini->left;
                mini->left = arr[j];
                if (arr[j]->key < mini->key)
                    mini = arr[j];
            } else {
                mini = arr[j];
            }
            if (mini == nullptr)
                mini = arr[j];
            else if (arr[j]->key < mini->key)
                mini = arr[j];
        }
    }
}


void Extract_min() {
    if (mini == nullptr)
        cout << "The heap is empty" << endl;
    else {
        node *temp = mini;
        node *pntr;
        pntr = temp;
        node *x = nullptr;
        if (temp->child != nullptr) {

            x = temp->child;
            do {
                pntr = x->right;
                (mini->left)->right = x;
                x->right = mini;
                x->left = mini->left;
                mini->left = x;
                if (x->key < mini->key)
                    mini = x;
                x->parent = nullptr;
                x = pntr;
            } while (pntr != temp->child);
        }
        (temp->left)->right = temp->right;
        (temp->right)->left = temp->left;
        mini = temp->right;
        if (temp == temp->right && temp->child == nullptr)
            mini = nullptr;
        else {
            mini = temp->right;
            Consolidate();
        }
        no_of_nodes--;
    }
}


void Cut(struct node *found, struct node *temp) {
    if (found == found->right)
        temp->child = nullptr;

    (found->left)->right = found->right;
    (found->right)->left = found->left;
    if (found == temp->child)
        temp->child = found->right;

    temp->degree = temp->degree - 1;
    found->right = found;
    found->left = found;
    (mini->left)->right = found;
    found->right = mini;
    found->left = mini->left;
    mini->left = found;
    found->parent = nullptr;
    found->mark = 'B';
}


void Cascase_cut(struct node *temp) {
    node *ptr5 = temp->parent;
    if (ptr5 != nullptr) {
        if (temp->mark == 'W') {
            temp->mark = 'B';
        } else {
            Cut(temp, ptr5);
            Cascase_cut(ptr5);
        }
    }
}


void Decrease_key(struct node *found, std::string val) {
    if (mini == nullptr)
        cout << "The Heap is Empty" << endl;

    if (found == nullptr)
        cout << "Node not found in the Heap" << endl;

    found->key.name = val;

    struct node *temp = found->parent;
    if (temp != nullptr && found->key < temp->key) {
        Cut(found, temp);
        Cascase_cut(temp);
    }
    if (found->key < mini->key)
        mini = found;
}


void Find(struct node *mini, Album old_val, std::string val) {
    struct node *found = nullptr;
    node *temp5 = mini;
    temp5->c = 'Y';
    node *found_ptr = nullptr;
    if (temp5->key == old_val) {
        found_ptr = temp5;
        temp5->c = 'N';
        found = found_ptr;
        Decrease_key(found, val);
    }
    if (found_ptr == nullptr) {
        if (temp5->child != nullptr)
            Find(temp5->child, old_val, val);
        if ((temp5->right)->c != 'Y')
            Find(temp5->right, old_val, val);
    }
    temp5->c = 'N';
    found = found_ptr;
}


void Deletion(Album val) {
    if (mini == nullptr)
        cout << "The heap is empty" << endl;
    else {

        // Decreasing the value of the node to 0
        Find(mini, val, min_str);

        // Calling Extract_min function to
        // delete minimum value node, which is 0
        Extract_min();
        cout << "Key Deleted" << endl;
    }
}

int count_sibling(const node *root) {
    if (!root)
        return 0;
    std::string temp = root->key.name;
    int res = 0;
    while (root->right && root->right->key.name != temp) {
        root = root->right;
        res++;
    }
    return res;
}


void queries() {
    while (true) {
        std::string command;
        getline(std::cin, command);
        if (command == "exit")
            break;
        if (command == "import data") {
            auto data = get_albums("../data");
            for (auto album: data)
                insertion(album);
            std::cout << "ok\n";
            continue;
        }
        if (command == "insert") {
            insertion(get_album());
            std::cout << "ok\n";
            continue;
        }
        if (command == "pop") {
            Extract_min();
            std::cout << "ok\n";
            continue;
        }
        if (command == "min") {

            print_album(mini->key);
            continue;
        }
        if (command == "delete") {
            Deletion(get_album());
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
