#include <iostream>

long long const inf = 1e9 + 7;
int const max_level = 1e3;

struct Node {
    int data;
    Node * next[max_level];
    Node(){
        data = 0;
    }
    Node (int d){
        data = d;
    }
};


struct SkipList {
    Node * head, * tail;
    int cnt_level;
    SkipList(){
        cnt_level = 0;
        head = new Node();
        tail = new Node();
        head->data = -inf;
        tail->data = inf;
        for (int i = 0; i < max_level; ++i)
            head->next[i] = tail;
    }
    std::pair <bool, Node*> find(int value){
        int cur_level = cnt_level - 1;
        Node *pointer;
        while (cur_level >= 0 && pointer->data != value){
            while (cur_level >= 0 && pointer->next[cur_level]->data > value) --cur_level;
            if (cur_level == -1) return {false, new Node()};
            else pointer = pointer->next[cur_level];
        }
        return {true, pointer};
    }
    int is_add(int level) {
        if (!level) return 1;
        return rand() % 2;
    }
    void add(int value){
        int cur_level = 0;
        while (is_add(cur_level)){
            Node *pointer = head;
            while (pointer->next[cur_level]->data < value) pointer = pointer->next[cur_level];
            Node *cur = new Node();
            cur->data = value;
            cur->next[cur_level] = pointer->next[cur_level];
            pointer->next[cur_level] = cur;
            ++cur_level;
        }
        cnt_level = std::max(cur_level, cnt_level);
    }
};

int main()
{
    int n;
    std::cin >> n;
    SkipList list = SkipList();
    for (int i = 1; i <= n; ++i){
        int temp;
        std::cin >> temp;
        list.add(temp);
    }
    for (int i = 0; i < list.cnt_level; ++i){
        Node *pointer = list.head;
        while (pointer != list.tail){
            std::cout << pointer->data << " ";
            pointer = pointer->next[i];
        }
        std::cout << "\n";
    }
    return 0;
}
