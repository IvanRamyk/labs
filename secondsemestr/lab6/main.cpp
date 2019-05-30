#include <iostream>
#include <ctime>
#include <cstdlib>
#include <vector>

struct Time{
    int hours;
    int minutes;
    void print(){
        std::cout << hours << ":" << minutes << "\n";
    }
    void get(){
        std::cin >> hours >> minutes;
    }
};

bool operator <(Time a, Time b){
    return a.hours * 60 + a.minutes < b.hours * 60 + b.minutes;
}

bool operator <=(Time a, Time b){
    return a.hours * 60 + a.minutes <= b.hours * 60 + b.minutes;
}

bool operator !=(Time a, Time b){
    return (a.minutes != b.minutes) || (a.hours != b.hours);
}

struct Date{
    int year;
    int month;
    int day;
    Time time;
    Date(){
        year = 0;
        month = 0;
        day = rand() % 30;
    }
    void print(){
        std::cout << day << "." << month << "." << year << "\n";
    }
    void get(){
        std::cin >> day >> month >> year;
    }
};

bool operator <(Date a, Date b ){
    return (a.year * 100 + a.month) * 20 + a.day < (b.year * 100 + b.month) * 20 + b.day ||
    ((a.year * 100 + a.month) * 20 + a.day == (b.year * 100 + b.month) * 20 + b.day && a.time < b.time);
}
bool operator <=(Date a, Date b ){
    return (a.year * 100 + a.month) * 20 + a.day <= (b.year * 100 + b.month) * 20 + b.day ||
           ((a.year * 100 + a.month) * 20 + a.day == (b.year * 100 + b.month) * 20 + b.day && a.time <= b.time);
}
bool operator !=(Date a, Date b){
    return (a.year != b.year) || (a.month != b.month) || (a.day != b.day) || (a.time != b.time);
}

struct Node{
    Node *next;
    Node *prev;
    Date date;
    Node(){
        date = Date();
        next = nullptr;
        prev = nullptr;
    }
    Node(Date _date, Node *n = nullptr, Node *p = nullptr){
        date = _date;
        next = n;
        prev = p;
    }
};

struct List{
    Node * head;
    Node * tail;
    List(){
        head = nullptr;
        tail = nullptr;
    }
    bool is_empty(){
        return !head;
    }
    void add(Date date){
        if (!head){
            head = tail = new Node(date);
        }
        else {
            if (date <= head->date) {
                Node *new_node = new Node(date, head);
                head->prev = new_node;
                head = new_node;
            }
            else {
                Node * current_ptr = head;
                while (!(date < current_ptr->date)){
                    if (current_ptr->next == nullptr) break;
                    current_ptr = current_ptr->next;
                }
                if (current_ptr == tail && (current_ptr->date < date)){
                    Node *new_node = new Node(date, nullptr, tail);
                    tail->next = new_node;
                    tail = new_node;
                }
                else {
                    Node *new_node = new Node(date, current_ptr, current_ptr->prev);
                    current_ptr->prev->next = new_node;
                    current_ptr->prev = new_node;
                }
            }
        }
    }
    void delete_date(Date date){
        Node * current_node = head;
        while (current_node != nullptr && current_node->date != date)
            current_node = current_node->next;
        if (current_node != nullptr){
            Node * begin = current_node->prev;
            while (current_node != nullptr && !(current_node->date != date))
                current_node = current_node->next;
            Node * end = current_node;
            if (begin == nullptr){
                if (end == nullptr){
                    head = tail = nullptr;
                }
                else {
                    head = end;
                    end->prev = nullptr;
                }
            }
            else if (end == nullptr){
                begin->next = nullptr;
            }
            else {
                begin->next = end;
                end->prev = begin;
            }
        }
    }
    void add_random(int cnt_random_nodes){
        for (int i = 0; i < cnt_random_nodes; ++i){
            add(Date());
        }
    }
    void print(){
        Node *cur =  head;
        while (cur != nullptr){
            cur->date.print();
            cur = cur->next;
        }
    }
    std::vector <Node *> find(Date min_value, Date max_value){
        std::vector <Node *> result;
        Node * current_node = head;
        while (current_node != nullptr){
            if (min_value <= current_node->date && current_node->date <= max_value)
                result.push_back(current_node);
            current_node = current_node->next;
        }
        return result;
    }
    std::vector <Node *> find(Date value){
        return find(value, value);
    }
};


struct binary_tree_node{
    Date date;
    binary_tree_node * left_child;
    binary_tree_node * right_child;
    binary_tree_node(){
        date = Date();
        left_child = nullptr;
        right_child = nullptr;
    }
    binary_tree_node(Date data, binary_tree_node * left, binary_tree_node * right){
        date = data;
        left_child = left;
        right_child = right;
    }
};

struct binary_tree{
    binary_tree_node * root;
    binary_tree(){
        root = nullptr;
    }
    binary_tree_node * add(Date data, binary_tree_node * current_node){
        if (current_node == nullptr){
            binary_tree_node * temp = new binary_tree_node(data, nullptr, nullptr);
            return temp;
        }
        if (data <= current_node->date)
            current_node->left_child = add(data, current_node->left_child);
        else
            current_node->right_child = add(data, current_node->right_child);
        return current_node;
    }
    void add(Date data){
        root = add(data, root);
    }
    void print_node_in_sort_order(binary_tree_node * current_node){
        if (current_node->left_child)
            print_node_in_sort_order(current_node->left_child);
        current_node->date.print();
        if (current_node->right_child)
            print_node_in_sort_order(current_node->right_child);
    }
    void print_in_sort_order(){
        if (root)
            print_node_in_sort_order(root);
    }
    void search_eps_node(binary_tree_node * current_node, std::vector<binary_tree_node *> &result, Date min_value, Date max_value){
        if (!current_node) return;
        if (min_value <= current_node->date && current_node->date <= max_value){
            result.push_back(current_node);
            search_eps_node(current_node->left_child, result, min_value, max_value);
            search_eps_node(current_node->right_child, result, min_value, max_value);
        }
        else {
            if (max_value < current_node->date)
                search_eps_node(current_node->left_child, result, min_value, max_value);
            else
                search_eps_node(current_node->right_child, result, min_value, max_value);
        }
    }
    std::vector <binary_tree_node *> search_eps(Date min_value, Date max_value){
        std::vector <binary_tree_node *> result;
        search_eps_node(root, result, min_value, max_value);
        return result;
    }
    binary_tree_node * get_min(binary_tree_node *current_node){
        if (current_node->left_child->left_child)
            return get_min(current_node->left_child);
        binary_tree_node * answer = current_node->left_child;
        current_node->left_child = current_node->left_child->right_child;
        return answer;
    }
    binary_tree_node * delete_member_node(binary_tree_node * current_node, Date min_value, Date max_value){
        if (!current_node) return current_node;
        if (min_value <= current_node->date && current_node->date <= max_value){
            if (!current_node->right_child){
                binary_tree_node * temp = current_node->left_child;
                delete current_node;
                return temp;
            }
            if (!current_node->right_child->left_child){
                binary_tree_node * temp = current_node->right_child;
                delete current_node;
                return temp;
            }
            else {
                binary_tree_node * temp = get_min(current_node->right_child);
                temp->left_child = current_node->left_child;
                temp->right_child = current_node->right_child;
                delete current_node;
                return temp;
            }
        }
        if (max_value < current_node->date)
            current_node->left_child = delete_member_node(current_node->left_child,  min_value, max_value);
        else
            current_node->right_child = delete_member_node(current_node->right_child, min_value, max_value);
        return current_node;
    }
    void delete_member(Date min_value, Date max_value){
        root = delete_member_node(root, min_value, max_value);
    }
};

int main() {
    srand(time(0));
    List _list = List();
    Date del = Date();
    _list.add(del);
    for (int i = 0; i < 10; ++i) {
        Date temp = Date();
        _list.add(temp);
        _list.add(temp);
        del = temp;
    }
    std::cout << "\n";
    _list.print();
    std::cout << "\n";
    _list.delete_date(del);
    del.print();
    std::cout << "\n";
    _list.print();
    return 0;
}
