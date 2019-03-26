#include <iostream>

using namespace std;

const int MaxMassageNumber = 10;

struct Massage{
    string text;
    int time_from_begin;
    Massage(){
        time_from_begin = 0;
        text = "";
    }
    Massage(int time, string massage){
        time_from_begin = time;
        text = massage;
    }
};

struct Node {
    Node *next;
    Node *prev;
    Massage massage;
    Node(){
        next = nullptr;
        prev = nullptr;
        massage = Massage();
    }
    Node(Node *n, Node *p, Massage m){
        next = n;
        prev = p;
        massage = m;
    }
};

struct List {
    Node *head;
    int MassageNumber;
    List(){
        head = nullptr;
        MassageNumber = 0;
    }
    bool is_empty(){
        return !head;
    }
    void append(Massage data){
        if (MassageNumber == MaxMassageNumber){
            head->prev->massage = data;
        }
        else MassageNumber++;

        if (!head){
            head = new Node(nullptr, nullptr, data);
            head->next = head;
            head->prev = head;
        }
        else {
            Node *temp = new Node(head, head->prev, data);
            head->prev->next = temp;
            head->prev = temp;
        }
    }
    void print(int number){
        Node *pointer = head;
        for (int i = 0; i < number; ++i){
            pointer = pointer->prev;
        }
        for (int i = 0; i < number; ++i){
            cout << pointer->massage.time_from_begin << ": " << pointer->massage.text << "\n";
            pointer = pointer->next;
        }
    }
};

int main() {
    List list = List();
    Massage temp;
    int n;
    cin >> n;
    getline(cin, temp.text);
    for (int i = 1; i <= n; ++i){
        getline(cin, temp.text);
        temp.time_from_begin = i;
        list.append(temp);
    }
    int k;
    cin >> k;
    list.print(k);
    return 0;
}
