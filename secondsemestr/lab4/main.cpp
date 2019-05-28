#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>

struct tree_node{
    int data;
    tree_node * parent;
    std::vector <tree_node *> children;
    tree_node(int _data, tree_node * _parent){
       parent = _parent;
       data = _data;
    }
};

double drand(double dmin, double dmax){
    return dmin + (dmax - dmin)*(rand())/RAND_MAX;
}

struct tree {
    std::vector <tree_node *> roots;
    tree(int data) {
        tree_node *root = new tree_node(data, nullptr);
        roots.push_back(root);
    }
    tree_node * add(tree_node * current_node, int data, double proc){
        if (drand(0,1) < proc){
            tree_node * new_node = new tree_node(data, current_node);
            current_node->children.push_back(new_node);
        }
        else if (current_node->children.size() != 0){
            int child = rand() % current_node->children.size();
            current_node->children[child] = add(current_node->children[child], data, 1 - proc);
        }
        return current_node;
    }
    void add(int data, double proc){
        roots[0] = add(roots[0], data, proc);
    }
    void inter_print(tree_node * current_node) {
        std::cout << "Current Node - " << current_node->data << "\n";
        std::cout << "Sons: ";
        for (int i = 0; i < current_node->children.size(); ++i)
            std::cout << current_node->children[i]->data << " ";
        std::cout << "\n";
        std::cout << "Enter q to exit\nEnter number from 0 to " << current_node->children.size()
                  << " to go to the child\nEnter b to go back\n";
        char to_do;
        std::cin >> to_do;
        if (to_do == 'q') return;
        else if (current_node->parent != nullptr && to_do == 'p') inter_print(current_node->parent);
        else if (current_node->parent == nullptr && to_do == 'p') return;
        else if (to_do - '0' < current_node->children.size() && to_do >= '0')
            inter_print(current_node->children[to_do - '0']);
        else inter_print(current_node);
    }
    void inter_print(){
        inter_print(roots[0]);
    }
    tree_node * delete_node(tree_node * current_node, int val){
        if (current_node->data == val && current_node->parent != nullptr){
            tree_node * parent = current_node->parent;
            for (int i = 0; i < current_node->children.size(); ++i)
                current_node->parent->children.push_back(current_node->children[i]);
            delete current_node;
            return nullptr;
        }
        for (int i = 0; i < current_node->children.size(); ++i) {
            current_node->children[i] = delete_node(current_node->children[i], val);
            if (!current_node->children[i]) {
                current_node->children.erase(current_node->children.begin() + i);
                i--;
            }
        }
        return current_node;
    }
    void delete_node(int val){
        roots[0] = delete_node(roots[0], val);
    }
};

struct binary_tree_node{
    int data;
    binary_tree_node * left_child;
    binary_tree_node * right_child;
    binary_tree_node * parent;
    binary_tree_node(int _data, binary_tree_node * left, binary_tree_node * right, binary_tree_node *_parent){
        data = _data;
        left_child = left;
        right_child = right;
        parent = _parent;
    }
};

struct binary_tree{
    binary_tree_node * root;
    binary_tree(){
        root = nullptr;
    }
    binary_tree_node * add(int data, binary_tree_node * current_node, binary_tree_node * _parent = nullptr){
        if (current_node == nullptr){
            binary_tree_node * temp = new binary_tree_node(data, nullptr, nullptr, _parent);
            return temp;
        }
        if (current_node->data >= data)
            current_node->left_child = add(data, current_node->left_child, current_node);
        else
            current_node->right_child = add(data, current_node->right_child, current_node);
        return current_node;
    }
    void add(int data){
        root = add(data, root);
    }
    void inter_print(binary_tree_node * current_node) {
        std::cout << "Current Node - " << current_node->data << "\n";
        std::cout << "Sons: ";
        int cnt_children = 0;
        if (current_node->left_child != nullptr)
            std::cout << "Left: " << current_node->left_child->data << " ";
        if (current_node->right_child != nullptr)
            std::cout << "Right: " << current_node->right_child->data;
        std::cout << "\n";
        std::cout << "Enter q to exit\nEnter l to go to the left child\nEnter r to go to the right child\n";
        char to_do;
        std::cin >> to_do;
        if (to_do == 'q') return;
        else if (current_node->parent != nullptr && to_do == 'p') inter_print(current_node->parent);
        else if (current_node->parent == nullptr && to_do == 'p') return;
        else if (to_do == 'l' && current_node->left_child != nullptr)
            inter_print(current_node->left_child);
        else if (to_do == 'r' && current_node->right_child != nullptr)
            inter_print(current_node->right_child);
        else inter_print(current_node);
    }
    void inter_print(){
        std::cout << "--------INTERACTOR PRINTING MODE----------\n";
        inter_print(root);
    }
    void symmetric_order(binary_tree_node * current_node, std::vector<binary_tree_node *> &answer){
        if (current_node->left_child != nullptr) {
            symmetric_order(current_node->left_child, answer);
        }
        answer.push_back(current_node);
        if (current_node->right_child != nullptr)
            symmetric_order(current_node->right_child, answer);
    }
    std::vector<binary_tree_node*> symmetric_order(){
        std::vector <binary_tree_node*> result;
        symmetric_order(root, result);
        return result;
    }
};

void inter_tree(){
    tree _tree = tree(0);
    std::string command;
    std::cout << "Enter 'add' to add element\n";
    std::cout << "Enter 'print' to start print mode\n";
    std::cout << "Enter 'exit' to exit\n";
    while (1){
        std::cin >> command;
        if (command == "exit") break;
        if (command == "add"){
            std::cout << "Print element, please\n";
            int data;
            std::cin >> data;
            _tree.add(data, drand(0, 1));
        }
        if (command == "print")
            _tree.inter_print();
    }
}

void inter_binary_tree(){
    binary_tree _tree = binary_tree();
    std::string command;
    std::cout << "Enter 'add' to add element\n";
    std::cout << "Enter 'print' to start print mode\n";
    std::cout << "Enter 'exit' to exit\n";
    while (1){
        std::cin >> command;
        if (command == "exit") break;
        if (command == "add"){
            std::cout << "Print element, please\n";
            int data;
            std::cin >> data;
            _tree.add(data);
        }
        if (command == "print")
            _tree.inter_print();
    }
}

void interactor(){
    std::cout << "Enter tree to work with tree\nEnter binary to work with binary tree\n";
    std::string command;
    std::cin >> command;
    if (command == "tree")
        inter_tree();
    if (command == "binary")
        inter_binary_tree();
}



void select(){
    std::cout << "Enter 'i' to start interactor mode\n";
    char mode;
    std::cin >> mode;
    if (mode == 'i') interactor();
}

int main() {
    srand(time(0));
    select();
    return 0;
}
