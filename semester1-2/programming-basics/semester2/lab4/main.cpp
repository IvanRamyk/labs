#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <unordered_map>
#include <chrono>
#include <thread>

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

struct expression_node{
    char type;//c - const, v - variable, o - operation
    int value;
};

struct expression_tree_node{
    expression_node data;
    expression_tree_node * left_child;
    expression_tree_node * right_child;
    expression_tree_node * parent;
    expression_tree_node(expression_node _data, expression_tree_node * left, expression_tree_node * right, expression_tree_node *_parent){
        data = _data;
        left_child = left;
        right_child = right;
        parent = _parent;
    }
};

bool is_unary(char operation){
    return operation == '-';
}

bool is_operation(char _char){
    return _char == '+' || _char == '-' || _char == '*' || _char == '/' || _char == '^';
}

int priority_operation(char operation){
    if (operation == '^') return 3;
    if (operation == '*' || operation == '/') return 2;
    if (operation == '+' || operation == '-') return 1;
    return 0;
}

struct expression_tree{
    expression_tree_node * root;
    std::unordered_map <char, int> variables;
    expression_tree(){
        root = nullptr;
    }
    expression_tree_node * expression_to_tree(std::string expression, expression_tree_node * parent = nullptr){
        if (is_unary(expression[0])){
            char operation = expression[0];
            expression.erase(expression.begin());
            expression_tree_node * current_node = new expression_tree_node({'o', operation},
                                                                     nullptr, expression_to_tree(expression), parent);
            return current_node;
        }
        while (1){
            if (expression[0] != '(' || expression[expression.size() - 1] != ')') break;
            bool can_delete = 1;
            int cnt = 0;
            for (int i = 1; i < expression.size() - 1; ++i){
                if (expression[i] == '(') ++cnt;
                if (expression[i] == ')') --cnt;
                if (cnt < 0) can_delete = 0;
            }
            if (!can_delete) break;
            expression.erase(expression.begin());
            expression.erase(expression.end() - 1);
        }
        int cnt_scope = 0, pos, pos_min_priority = -1, scope_min_priority = 1000;
        std::string first_expression = "";
        std::string second_expression = "";
        for (pos = 0; pos < expression.size(); ++pos) {
            if (expression[pos] == '(')
                ++cnt_scope;
            if (expression[pos] == ')')
                --cnt_scope;
            if (is_operation(expression[pos]) && ((scope_min_priority > cnt_scope)
            || (scope_min_priority == cnt_scope && priority_operation(expression[pos])< priority_operation(expression[pos_min_priority])))) {
                pos_min_priority = pos;
                scope_min_priority = cnt_scope;
            }
        }
        if (pos_min_priority == -1){
            char first_operand_type;
            int first_operand_value;
            if (expression[0] <= '9' && expression[0] >= '0') {
                first_operand_type = 'c';
                first_operand_value = std::atoi(expression.c_str());
            }
            else {
                first_operand_type = 'v';
                first_operand_value = expression[0] - 'a';
            }
            expression_tree_node * current_node = new expression_tree_node({first_operand_type, first_operand_value},
                                                                           nullptr, nullptr, parent);
            return current_node;
        }
        char operation = expression[pos_min_priority];
        for (int i = 0; i < pos_min_priority; ++i)
            first_expression += expression[i];
        for (int i = pos_min_priority + 1; i < expression.size(); ++i)
            second_expression += expression[i];
        expression_tree_node * current_node = new expression_tree_node({'o', operation}, expression_to_tree(first_expression),
                                                                       expression_to_tree(second_expression), parent);
        return current_node;

    }
    void get_expression(std::string expression){
        std::string formating = "";
        for (int i = 0; i < expression.size(); ++i)
            if (expression[i] != ' ')
                formating += expression[i];
        root = expression_to_tree(formating);
    }
    void print_expression(expression_tree_node * current_node){
        if (current_node->data.type == 'o' && current_node->left_child != nullptr){
            if (current_node->left_child->data.type == 'o' &&
                priority_operation(current_node->data.value) > priority_operation(current_node->left_child->data.value))
                std::cout << "(";
            print_expression(current_node->left_child);
            if (current_node->left_child->data.type == 'o' &&
                priority_operation(current_node->data.value) > priority_operation(current_node->left_child->data.value))
                std::cout << ")";
            std::cout << char(current_node->data.value);
            if (current_node->right_child->data.type == 'o' &&
                priority_operation(current_node->data.value) >= priority_operation(current_node->right_child->data.value))
                std::cout << "(";
            print_expression(current_node->right_child);
            if (current_node->right_child->data.type == 'o' &&
                priority_operation(current_node->data.value) >= priority_operation(current_node->right_child->data.value))
                std::cout << ")";
        }
        else if (current_node->data.type == 'o' && is_unary(current_node->data.value)){
            std::cout << char(current_node->data.value);
            if (current_node->right_child->data.type == 'o')
                std::cout << "(";
            print_expression(current_node->right_child);
            if (current_node->right_child->data.type == 'o')
                std::cout << ")";
        }
        else if (current_node->data.type == 'c'){
            std::cout << current_node->data.value;
        }
        else {
            std::cout << char('a' + current_node->data.value);
        }
    }
    void print_expression(){
        print_expression(root);
        std::cout << "\n";
    }
    void inter_print(expression_tree_node * current_node) {
        std::cout << "Current Node - ";
        if (current_node->data.type == 'o')
            std::cout << char(current_node->data.value) << "\n";
        if (current_node->data.type == 'c')
            std::cout << current_node->data.value << "\n";
        if (current_node->data.type == 'v')
            std::cout << char(current_node->data.value + 'a') << "\n";
        std::cout << "Sons: ";
        int cnt_children = 0;
        if (current_node->left_child != nullptr)
            std::cout << "Left: " << current_node->left_child->data.value << " ";
        if (current_node->right_child != nullptr)
            std::cout << "Right: " << current_node->right_child->data.value;
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
    void delete_node(expression_tree_node * current_node){
        if (current_node->left_child)
            delete_node(current_node->left_child);
        if (current_node->right_child)
            delete_node(current_node->left_child);
        delete current_node;
    }
    std::pair<bool, expression_tree_node *> calculate_const(expression_tree_node * current_node){
        if (current_node->data.type == 'v')
            return {0, current_node};
        if (current_node->data.type == 'c')
            return {1, current_node};
        std::pair<bool, expression_tree_node *> first = calculate_const(current_node->left_child);
        std::pair<bool, expression_tree_node *> second = calculate_const(current_node->right_child);
        current_node->left_child = first.second;
        current_node->right_child = second.second;
        bool answer = first.first && second.first;
        if (answer){
            current_node->data.type = 'c';
            if (current_node->data.value == int('-'))
                current_node->data.value = current_node->left_child->data.value - current_node->right_child->data.value;
            if (current_node->data.value == int('+'))
                current_node->data.value = current_node->left_child->data.value + current_node->right_child->data.value;
            if (current_node->data.value == int('*'))
                current_node->data.value = current_node->left_child->data.value * current_node->right_child->data.value;
            if (current_node->data.value == int('/') && current_node->right_child->data.value != 0)
                current_node->data.value = current_node->left_child->data.value / current_node->right_child->data.value;
            if (current_node->data.value == int('/') && current_node->right_child->data.value == 0) {
                current_node->data.type = 'o';
                return {0, current_node};
            }
            if (current_node->data.value == int('^'))
                current_node->data.value = std::pow(current_node->left_child->data.value, current_node->right_child->data.value);
            delete_node(current_node->left_child);
            delete_node(current_node->right_child);
            current_node->left_child = nullptr;
            current_node->right_child = nullptr;
        }
        return {answer, current_node};
    }
    void calculate_const(){
        root = calculate_const(root).second;
    }
    expression_tree_node * simplify(expression_tree_node * current_node){
        if (current_node->left_child != nullptr)
            simplify(current_node->left_child);
        if (current_node->right_child != nullptr)
            simplify(current_node->right_child);
        if (current_node->data.type == 'o'){
            //1*a = a
            if (char(current_node->data.value) == '*'
            && (current_node->right_child->data.value  == 1 && current_node->right_child->data.type == 'c')){
                current_node->data.type = current_node->left_child->data.type;
                current_node->data.value = current_node->left_child->data.value;
                current_node->left_child = nullptr;
                current_node->right_child = nullptr;
            }
            if (char(current_node->data.value) == '*'
                && (current_node->left_child->data.value  == 1 && current_node->left_child->data.type == 'c')){
                current_node->data.type = current_node->right_child->data.type;
                current_node->data.value = current_node->right_child->data.value;
                current_node->left_child = nullptr;
                current_node->right_child = nullptr;
            }
            //0*a=0
            if (char(current_node->data.value) == '*'
                && (current_node->left_child->data.value  == 0 && current_node->left_child->data.type == 'c')){
                current_node->data.type = 'c';
                current_node->data.value = 0;
                current_node->left_child = nullptr;
                current_node->right_child = nullptr;
            }
            if (char(current_node->data.value) == '*'
                && (current_node->left_child->data.value  == 0 && current_node->left_child->data.type == 'c')){
                current_node->data.type = 'c';
                current_node->data.value = 0;
                current_node->left_child = nullptr;
                current_node->right_child = nullptr;
            }
            //a+-0
            if ((char(current_node->data.value) == '-' || char(current_node->data.value) == '+')
                && (current_node->right_child->data.value  == 0 && current_node->right_child->data.type == 'c')){
                current_node->data.type = current_node->left_child->data.type;
                current_node->data.value = current_node->left_child->data.value;
                current_node->left_child = nullptr;
                current_node->right_child = nullptr;
            }
            if ((char(current_node->data.value) == '-' || char(current_node->data.value) == '+')
                && (current_node->left_child->data.value  == 0 && current_node->left_child->data.type == 'c')){
                current_node->data.type = current_node->right_child->data.type;
                current_node->data.value = current_node->right_child->data.value;
                current_node->left_child = nullptr;
                current_node->right_child = nullptr;
            }
            //0/a
            if (char(current_node->data.value) == '/'
                && (current_node->left_child->data.value  == 0 && current_node->left_child->data.type == 'c')){
                current_node->data.type = 'c';
                current_node->data.value = 0;
                current_node->left_child = nullptr;
                current_node->right_child = nullptr;
            }
        }
        return current_node;
    }
    void simplify(){
        calculate_const();
        root = simplify(root);
    }
    int calculate(expression_tree_node * current_node){
        if (current_node->data.type == 'v'){
            if (variables.count(char(current_node->data.value + 'a'))) {
                return variables[char(current_node->data.value + 'a')];
            }
            else {
                std::cout << "Enter " << char(current_node->data.value + 'a') << " value, please\n";
                int value;
                std::cin >> value;
                return variables[char(current_node->data.value + 'a')] = value;
            }
        }
        if (current_node->data.type == 'c')
            return current_node->data.value;
        int first_result = calculate(current_node->left_child);
        int second_result = calculate(current_node->right_child);
        if (current_node->data.value == int('-'))
            return first_result - second_result;
        if (current_node->data.value == int('+'))
            return first_result + second_result;
        if (current_node->data.value == int('*'))
            return first_result * second_result;
        if (current_node->data.value == int('/'))
            return first_result / second_result;
        if (current_node->data.value == int('^'))
            return first_result ^ second_result;
        return 0;
    }
    int calculate(std::vector <std::pair<char, int>> _variables = {}){
        for (int i = 0; i < _variables.size(); ++i)
            variables[_variables[i].first] = _variables[i].second;
        return calculate(root);
    }
    bool is_mistakes(expression_tree_node * current_node){
        if (current_node->left_child != nullptr)
            if (is_mistakes(current_node->left_child))
                return 1;
        if (current_node->right_child != nullptr)
            if (is_mistakes(current_node->right_child))
                return 1;
        if (current_node->data.type == 'o' && char(current_node->data.value) == '/' && current_node->right_child->data.value == 0)
            return 1;
        return 0;
    }
    bool is_mistakes(){
        calculate_const();
        return is_mistakes(root);
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

void print_list_commands_expression(){
    std::cout << "Enter 'new' to work with new expression\n"
                 "Enter 'print' to print expression\n"
                 "Enter 'exit' to stop working\n"
                 "Enter 'simplify' to simplify expression\n"
                 "Enter 'calculate' to calculate expression\n";
}

void inter_expression(){
    expression_tree _tree;
    print_list_commands_expression();
    while (1){
        std::string command;
        std::cin >> command;
        if (command == "exit") break;
        if (command == "new") {
            std::cout << "Please, enter expression\n";
            bool not_valid = 1;
            while (not_valid){
                not_valid = 0;
                std::string new_expression;
                std::cin >> new_expression;
                _tree.get_expression(new_expression);
                if (_tree.is_mistakes()) {
                    not_valid = 1;
                    std::cout << "Invalid expression. Try again\n";
                }
            }
            std::cout << "ok\n";
        }
        if (command == "simplify"){
            _tree.simplify();
            std::cout << "ok\n";
        }
        if (command == "print"){
            _tree.print_expression();
            std::cout << "ok\n";
        }
        if (command == "calculate"){
            std::cout << _tree.calculate() << "\n";
            std::cout << "ok\n";
        }
    }
}

void interactor(){
    std::cout << "-----------INTERACTOR MODE------------\n";
    std::cout << "Enter 'tree' to work with tree\n"
                 "Enter 'binary' to work with binary tree\n"
                 "Enter 'expression' to work with expression\n";
    std::string command;
    std::cin >> command;
    if (command == "tree")
        inter_tree();
    if (command == "binary")
        inter_binary_tree();
    if (command == "expression")
        inter_expression();
}

void sleep_for_demo(){
    int sleep_for_time = 1000;
    std::this_thread::sleep_for(std::chrono::milliseconds(sleep_for_time));
}

void demo(){
    std::cout << "-----------DEMO MODE------------\n";
    std::cout << "Working with tree:\n";
    sleep_for_demo();
    tree _tree(-1);
    std::cout << "Add -1, 2, 3, 4, 5, 10, 13:\n";
    sleep_for_demo();
    _tree.add(2, drand(0, 1));
    _tree.add(3, drand(0, 1));
    _tree.add(4, drand(0, 1));
    _tree.add(5, drand(0, 1));
    _tree.add(10, drand(0, 1));
    _tree.add(13, drand(0, 1));
    std::cout << "Printing tree is interactive, you need to chose options\n";
    sleep_for_demo();
    _tree.inter_print();
    std::cout << "Delete 2, 3, 10\n";
    _tree.delete_node(2);
    _tree.delete_node(3);
    _tree.delete_node(10);
    std::cout << "Printing tree is interactive, you need to chose options\n";
    sleep_for_demo();
    _tree.inter_print();
    std::cout << "Working with binary tree\n";
    sleep_for_demo();
    binary_tree binary;
    std::cout << "Add 9, 1, 2, 5, 15, 34, 23, 14\n";
    sleep_for_demo();
    binary.add(9);
    binary.add(1);
    binary.add(2);
    binary.add(5);
    binary.add(15);
    binary.add(34);
    binary.add(23);
    binary.add(14);
    std::cout << "Printing tree is interactive, you need to chose options\n";
    sleep_for_demo();
    binary.inter_print();
    std::cout << "Working with expression\n";
    std::cout << "Add expression '(3+2)/a + b'\n";
    expression_tree expression;
    expression.get_expression("(3+2)/a + b");
    std::cout << "Print expression\n";
    expression.print_expression();
    std::cout <<"Simplify expression '(1*5-5)/(123-b) + (5 - 5) * c'\n";
    expression.get_expression("(1*5-5)/(123-b) + (5 - 5) * c");
    expression.simplify();
    expression.print_expression();
    std::cout <<"Calculate expression '(3 + a)/b + 123 + c*a'\n"
                "a == 1\n"
                "b == 2\n"
                "c == 3\n";
    expression.get_expression("(3 + a)/b + 123 + c*a");
    std::cout << expression.calculate({{'a',1}, {'b', 2},{'c', 3}}) << "\n";
    std::cout << "Have a nice day!\n";
}

void select(){
    std::cout << "Enter 'i' to start interactor mode\n"
                 "Enter 'd' to start demo mode\n";
    char mode;
    std::cin >> mode;
    if (mode == 'i') interactor();
    if (mode == 'd') demo();
}

int main() {
    srand(time(0));
    select();
    return 0;
}
