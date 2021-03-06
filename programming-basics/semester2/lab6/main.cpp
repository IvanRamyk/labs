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

struct node{
    node *next;
    node *prev;
    Date date;
    node(){
        date = Date();
        next = nullptr;
        prev = nullptr;
    }
    node(Date _date, node *n = nullptr, node *current_node = nullptr){
        date = _date;
        next = n;
        prev = current_node;
    }
};

struct list{
    node * head;
    node * tail;
    list(){
        head = nullptr;
        tail = nullptr;
    }
    bool is_empty(){
        return !head;
    }
    void add(Date date){
        if (!head){
            head = tail = new node(date);
        }
        else {
            if (date <= head->date) {
                node *new_node = new node(date, head);
                head->prev = new_node;
                head = new_node;
            }
            else {
                node * current_ptr = head;
                while (!(date < current_ptr->date)){
                    if (current_ptr->next == nullptr) break;
                    current_ptr = current_ptr->next;
                }
                if (current_ptr == tail && (current_ptr->date < date)){
                    node *new_node = new node(date, nullptr, tail);
                    tail->next = new_node;
                    tail = new_node;
                }
                else {
                    node *new_node = new node(date, current_ptr, current_ptr->prev);
                    current_ptr->prev->next = new_node;
                    current_ptr->prev = new_node;
                }
            }
        }
    }
    void delete_date(Date date){
        node * current_node = head;
        while (current_node != nullptr && current_node->date != date)
            current_node = current_node->next;
        if (current_node != nullptr){
            node * begin = current_node->prev;
            while (current_node != nullptr && !(current_node->date != date))
                current_node = current_node->next;
            node * end = current_node;
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
        node *cur =  head;
        while (cur != nullptr){
            cur->date.print();
            cur = cur->next;
        }
    }
    std::vector <node *> find(Date min_value, Date max_value){
        std::vector <node *> result;
        node * current_node = head;
        while (current_node != nullptr){
            if (min_value <= current_node->date && current_node->date <= max_value)
                result.push_back(current_node);
            current_node = current_node->next;
        }
        return result;
    }
    std::vector <node *> find(Date value){
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
    void find(binary_tree_node * current_node, std::vector<binary_tree_node *> &result, Date min_value, Date max_value){
        if (!current_node) return;
        if (min_value <= current_node->date && current_node->date <= max_value){
            result.push_back(current_node);
            find(current_node->left_child, result, min_value, max_value);
            find(current_node->right_child, result, min_value, max_value);
        }
        else {
            if (max_value < current_node->date)
                find(current_node->left_child, result, min_value, max_value);
            else
                find(current_node->right_child, result, min_value, max_value);
        }
    }
    std::vector <binary_tree_node *> find(Date min_value, Date max_value){
        std::vector <binary_tree_node *> result;
        find(root, result, min_value, max_value);
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
        if (current_node == nullptr) return current_node;
        if (min_value <= current_node->date && current_node->date <= max_value){
            current_node->left_child = delete_member_node(current_node->left_child, min_value, max_value);
            current_node->right_child = delete_member_node(current_node->right_child, min_value, max_value);
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
    void delete_member(Date value){
        root = delete_member_node(root, value, value);
    }
    void add_random(int cnt_random){
        for (int i = 0;i <  cnt_random; ++i){
            Date temp = Date();
            add(temp);
        }
    }
};

const int list_size = 100;

struct array_list{
    Date dates[list_size];
    int cnt_dates_in_list;
    array_list(){
        cnt_dates_in_list = 0;
    }
    void add(Date date){
        if (cnt_dates_in_list == 0){
            dates[0] = date;
            cnt_dates_in_list++;
            return;
        }
        int left = 0;
        int right = cnt_dates_in_list;
        while (right - left > 1){
            int middle = (right + left) >> 1;
            if (date < dates[middle])
                right = middle;
            else
                left = middle;
        }
        int pos;
        if (date < dates[left])
            pos = left;
        else
            pos = left + 1;
        for (int i = cnt_dates_in_list; i > pos; --i)
            dates[i] = dates[i - 1];
        dates[pos] = date;
        cnt_dates_in_list++;
    }
    void print_in_sort_order(){
        for (int i = 0; i < cnt_dates_in_list; ++i)
            dates[i].print();
    }
    void delete_date(Date date){
        int left = 0;
        int right = cnt_dates_in_list;
        while (right - left > 1){
            int middle = (right + left) >> 1;
            if (date <= dates[middle])
                right = middle;
            else
                left = middle;
        }
        int pos = left;
        while (pos < cnt_dates_in_list && dates[pos] < date)
            ++pos;
        int begin = pos;
        while (pos < cnt_dates_in_list && (!(date < dates[pos])))
            pos++;
        int end = pos;
        int cnt_delete = end - begin;
        if (cnt_delete == 0) return;
        for (int i = begin; i < cnt_dates_in_list - cnt_delete; ++i)
            dates[i] = dates[i + cnt_delete];
        cnt_dates_in_list -= cnt_delete;
    }
    std::vector <Date> find(Date min_value, Date max_value){
        std::vector<Date> result;
        int left = 0;
        int right = cnt_dates_in_list;
        while (right - left > 1){
            int middle = (right + left) >> 1;
            if (min_value <= dates[middle])
                right = middle;
            else
                left = middle;
        }
        int L;
        if (min_value <= dates[left])
            L = left;
        else
            L = left + 1;
        left = 0;
        right = cnt_dates_in_list;
        while (right - left > 1){
            int middle = (right + left) >> 1;
            if (min_value < dates[middle])
                right = middle;
            else
                left = middle;
        }
        int R = left;
        for (int i = L; i <= R; ++i)
            result.push_back(dates[i]);
        return result;
    }
    std::vector<Date>find(Date value){
        return find(value, value);
    }
    void add_random(int cnt_random){
        for (int i = 0;i <  cnt_random; ++i){
            Date temp = Date();
            add(temp);
        }
    }
};

struct balance_tree_node{
    Date date;
    unsigned char height;
    balance_tree_node* left_child;
    balance_tree_node* right_child;
    balance_tree_node(Date _date) { 
        date = _date; 
        left_child = right_child = nullptr; 
        height = 1; 
    }
};

struct balance_tree{
    balance_tree_node * root;
    balance_tree(){
        root = nullptr;
    }
    unsigned char height(balance_tree_node* current_node){
        if (current_node != nullptr) return current_node->height;
        return 0;
    }
    int balance_factor(balance_tree_node* current_node){
        return height(current_node->right_child)-height(current_node->left_child);
    }
    void get_hight(balance_tree_node* current_node){
        unsigned char hl = height(current_node->left_child);
        unsigned char hr = height(current_node->right_child);
        current_node->height = (hl>hr?hl:hr)+1;
    }
    balance_tree_node* rotate_right(balance_tree_node* current_node){
        balance_tree_node* q = current_node->left_child;
        current_node->left_child = q->right_child;
        q->right_child = current_node;
        get_hight(current_node);
        get_hight(q);
        return q;
    }
    balance_tree_node* rotate_left(balance_tree_node* q){
        balance_tree_node* current_node = q->right_child;
        q->right_child = current_node->left_child;
        current_node->left_child = q;
        get_hight(q);
        get_hight(current_node);
        return current_node;
    }
    balance_tree_node* balance(balance_tree_node* current_node){
        get_hight(current_node);
        if( balance_factor(current_node)==2 ){
            if( balance_factor(current_node->right_child) < 0 )
                current_node->right_child = rotate_right(current_node->right_child);
            return rotate_left(current_node);
        }
        if( balance_factor(current_node)==-2 ){
            if( balance_factor(current_node->left_child) > 0  )
                current_node->left_child = rotate_left(current_node->left_child);
            return rotate_right(current_node);
        }
        return current_node;
    }
    balance_tree_node* add(balance_tree_node* current_node, Date _date){
        if( !current_node ) return new balance_tree_node(_date);
        if( _date<current_node->date )
            current_node->left_child = add(current_node->left_child, _date);
        else
            current_node->right_child = add(current_node->right_child, _date);
        return balance(current_node);
    }
    void add(Date date){
        root = add(root, date);
    }
    balance_tree_node* find_minimum(balance_tree_node* current_node) {
        return current_node->left_child?find_minimum(current_node->left_child):current_node;
    }
    balance_tree_node* remove_minimum(balance_tree_node* current_node){
        if( current_node->left_child==0 )
            return current_node->right_child;
        current_node->left_child = remove_minimum(current_node->left_child);
        return balance(current_node);
    }
    balance_tree_node* remove(balance_tree_node* current_node, Date min_date, Date max_date) {
        if(!current_node) return 0;
        if(max_date < current_node->date)
            current_node->left_child = remove(current_node->left_child,min_date, max_date);
        else if(current_node->date < min_date)
            current_node->right_child = remove(current_node->right_child,min_date, max_date);
        else
        {
            current_node->left_child = remove(current_node->left_child, min_date, max_date);
            current_node->right_child = remove(current_node->right_child, min_date, max_date);
            balance_tree_node* q = current_node->left_child;
            balance_tree_node* r = current_node->right_child;
            delete current_node;
            if(!r) return q;
            balance_tree_node* min = find_minimum(r);
            min->right_child = remove_minimum(r);
            min->left_child = q;
            return balance(min);
        }
        return balance(current_node);
    }
    void remove(Date min_date, Date max_date){
        root = remove(root, min_date, max_date);
    }
    void remove(Date date){
        root = remove(root, date, date);
    }
    void find(balance_tree_node * current_node, std::vector<balance_tree_node *> &result, Date min_value, Date max_value){
        if (!current_node) return;
        if (min_value <= current_node->date && current_node->date <= max_value){
            result.push_back(current_node);
            find(current_node->left_child, result, min_value, max_value);
            find(current_node->right_child, result, min_value, max_value);
        }
        else {
            if (max_value < current_node->date)
                find(current_node->left_child, result, min_value, max_value);
            else
                find(current_node->right_child, result, min_value, max_value);
        }
    }
    std::vector <balance_tree_node *> find(Date min_value, Date max_value){
        std::vector <balance_tree_node *> result;
        find(root, result, min_value, max_value);
        return result;
    }
    std::vector <balance_tree_node *> find(Date value){
        std::vector <balance_tree_node *> result;
        find(root, result, value, value);
        return result;
    }
    void print_in_sort_order(balance_tree_node * current_node){
        if (current_node == nullptr) return;
        print_in_sort_order(current_node->left_child);
        current_node->date.print();
        print_in_sort_order(current_node->right_child);
    }
    void print_in_sort_order(){
        print_in_sort_order(root);
    }
};


int main() {
    srand(time(0));
    balance_tree _tree = balance_tree();
    Date del;
    for (int i = 0; i < 10; ++i) {
        Date temp = Date();
        _tree.add(temp);
        _tree.add(temp);
        del = temp;
        temp.print();
    }
    std::cout << "\n";
    _tree.print_in_sort_order();
    std::cout << "\n";
    std::vector<balance_tree_node * > vec = _tree.find(del);
    for (auto i : vec)
        i->date.print();
    _tree.remove(del);
    std::cout << "\n";
    _tree.print_in_sort_order();
    return 0;
}
