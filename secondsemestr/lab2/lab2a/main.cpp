#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <cmath>
#include <ctime>
#include <windows.h>

using namespace std;

const int nmax = 50000;
const int sleep_time = 1000;

struct IP{
    string IP4;
    IP(){
        IP4 = "";
    }
    IP(string ip){
        IP4 = ip;
    }
    bool is_valid(string temp_ip){
        string field = "";
        int cnt_fields = 1;
        if (temp_ip[temp_ip.size() - 1] == '.') return 0;
        for (int i = 0; i < temp_ip.size(); ++i){
            if ((temp_ip[i] > '9' || temp_ip[i] < '0') && temp_ip[i] != '.') return 0;
            if (temp_ip[i] == '.') {
                if (field == "") return 0;
                ++cnt_fields;
                int field_val = atoi(field.c_str());
                if (field_val < 0 || field_val > 255) return 0;
                field = "";
            }
            else field += temp_ip[i];
        }
        if (field == "") return 0;
        int field_val = atoi(field.c_str());
        if (field_val < 0 || field_val > 255) return 0;
        if (cnt_fields != 4) return 0;
        return 1;
    }
    bool get(){
        string ip;
        cin >> ip;
        if (is_valid(ip)){
            IP4 = ip;
            return 1;
        }
        return 0;
    }
    void print(){
        cout << IP4 << "\n";
    }
    void random_value(){
        IP4 = "";
        int field = rand() % 256;
        IP4 += to_string(field);
        IP4 += '.';
        field = rand() % 256;
        IP4 += to_string(field);
        IP4 += '.';
        field = rand() % 256;
        IP4 += to_string(field);
        IP4 += '.';
        field = rand() % 256;
        IP4 += to_string(field);
    }
};

struct Node{
    Node *next;
    Node *prev;
    IP IP4;
    Node(){
        IP4 = IP();
        next = nullptr;
        prev = nullptr;
    }
    Node(IP ip, Node *n = nullptr, Node *p = nullptr){
        IP4 = ip;
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
    void append_left(IP ip){
        if (!head){
            head = tail = new Node(ip);
        }
        else {
            Node *cur = new Node(ip, head);
            head->prev = cur;
            head = cur;
        }
    }
    void append_right(IP ip){
        if (!head){
            head = tail = new Node(ip);
        }
        else {
            Node *cur = new Node(ip, nullptr, tail);
            tail->next = cur;
            tail = cur;
        }
    }
    IP front(){
        return head->IP4;
    }
    IP back(){
        return tail->IP4;
    }
    bool pop_left(){
        if (is_empty()) return 0;
        if (head == tail){
            head = tail = nullptr;
        }
        else {
            Node *temp = head;
            head = head->next;
            head->prev = nullptr;
            delete temp;
        }
        return 1;
    }
    bool pop_right(){
        if (is_empty()) return 0;
        if (head == tail){
            head = tail = nullptr;
        }
        else {
            Node *temp = tail;
            tail = tail->prev;
            tail->next = nullptr;
            delete temp;
        }
        return 1;
    }
    void print(){
        Node *cur =  head;
        while (cur != nullptr){
            cur->IP4.print();
            cur = cur->next;
        }
    }
};

struct Array{
    IP arr[nmax];
    int number_in_struct;
    Array(){
        number_in_struct = 0;
    }
    bool is_empty(){
        return !number_in_struct;
    }
    bool append_right(IP IP4){
        if (number_in_struct == nmax) return 0;
        arr[number_in_struct] = IP4;
        ++number_in_struct;
        return 1;
    }
    bool append_left(IP IP4){
        if (number_in_struct == nmax) return 0;
        for (int pos = number_in_struct; pos; pos--)
            arr[pos] = arr[pos - 1];
        arr[0] = IP4;
        number_in_struct++;
        return 1;
    }
    bool pop_right(){
        if (is_empty()) return 0;
        number_in_struct--;
    }
    bool pop_left(){
        if(is_empty()) return 0;
        for (int pos = 0; pos < number_in_struct - 1; ++pos)
            arr[pos] = arr[pos + 1];
        number_in_struct--;
    }
    void print(){
        for (int pos = 0; pos < number_in_struct; ++pos)
            arr[pos].print();
    }
};

struct Vector{
    vector <IP> vec;
    Vector(){
        vec.clear();
    }
    bool is_empty(){
        return vec.empty();
    }
    void append_right(IP IP4){
        vec.push_back(IP4);
    }
    void append_left(IP IP4){
        vec.insert(vec.begin(), IP4);
    }
    bool pop_right(){
        if (is_empty()) return 0;
        vec.pop_back();
    }
    bool pop_left(){
        if(is_empty()) return 0;
        vec.erase(vec.begin());
    }
    void print(){
        for(auto i : vec)
            i.print();
    }
};

void print_command_list(){
    cout << "q //exit\nis_empty // print is struct empty\nappend_left <IP4> //add IP4 to the head of queue\nappend_right <IP4>//add IP4 to the tail of queue\npop_left // remove element from head\npop_right //remove element from tail\n print //print elements from head to tail\n";
}

void ok(){
    cout << "OK\n";
}

void interacter_array(){
    Array adress = Array();
    cout << "Press 'h' to view list of commands\n";
    while (1){
        string command_type;
        cin >> command_type;
        if (command_type == "q") break;
        if (command_type == "h") print_command_list();
        if (command_type == "append_left"){
            IP ip;
            if (ip.get()){
                if (adress.append_left(ip)){
                    ok();
                }
                else {
                    cout << "ERROR: number of IP's is already maximum.\n";
                }
            }
            else {
                cout << "ERROR: invalid IP4.\n";
            }
        }
        if (command_type == "append_right"){
            IP ip;
            if (ip.get()){
                if (adress.append_right(ip)){
                    ok();
                }
                else {
                    cout << "ERROR: number of IP's is already maximum.\n";
                }
            }
            else {
                cout << "ERROR: invalid IP4.\n";
            }
        }
        if (command_type == "is_empty"){
            if (adress.is_empty()) cout << "YES\n";
            else cout << "NO\n";
        }
        if (command_type == "pop_left"){
            if (adress.pop_left()) ok();
            else cout << "ERROR: struct is empty\n";
        }
        if (command_type == "pop_right"){
            if (adress.pop_right()) ok();
            else cout << "ERROR: struct is empty\n";
        }
        if (command_type == "print"){
            adress.print();
        }
    }
}

void interacter_vector(){
    Vector adress = Vector();
    cout << "Press 'h' to view list of commands\n";
    while (1){
        string command_type;
        cin >> command_type;
        if (command_type == "q") break;
        if (command_type == "h") print_command_list();
        if (command_type == "append_left"){
            IP ip;
            if (ip.get()){
                adress.append_left(ip);
                ok();
            }
            else {
                cout << "ERROR: invalid IP4.\n";
            }
        }
        if (command_type == "append_right"){
            IP ip;
            if (ip.get()){
                adress.append_right(ip);
                ok();
            }
            else {
                cout << "ERROR: invalid IP4.\n";
            }
        }
        if (command_type == "is_empty"){
            if (adress.is_empty()) cout << "YES\n";
            else cout << "NO\n";
        }
        if (command_type == "pop_left"){
            if (adress.pop_left()) ok();
            else cout << "ERROR: struct is empty\n";
        }
        if (command_type == "pop_right"){
            if (adress.pop_right()) ok();
            else cout << "ERROR: struct is empty\n";
        }
        if (command_type == "print"){
            adress.print();
        }
    }
}

void interacter_list(){
    List adress = List();
    cout << "Press 'h' to view list of commands\n";
    while (1){
        string command_type;
        cin >> command_type;
        if (command_type == "q") break;
        if (command_type == "h") print_command_list();
        if (command_type == "append_left"){
            IP ip;
            if (ip.get()){
                adress.append_left(ip);
                ok();
            }
            else {
                cout << "ERROR: invalid IP4.\n";
            }
        }
        if (command_type == "append_right"){
            IP ip;
            if (ip.get()){
                adress.append_right(ip);
                ok();
            }
            else {
                cout << "ERROR: invalid IP4.\n";
            }
        }
        if (command_type == "is_empty"){
            if (adress.is_empty()) cout << "YES\n";
            else cout << "NO\n";
        }
        if (command_type == "pop_left"){
            if (adress.pop_left()) ok();
            else cout << "ERROR: struct is empty\n";
        }
        if (command_type == "pop_right"){
            if (adress.pop_right()) ok();
            else cout << "ERROR: struct is empty\n";
        }
        if (command_type == "print"){
            adress.print();
        }
    }
}

void interacter(){
    cout << "-------INTERACTOR MODE-------\nChoose type of struct:\nPress 'l' to use list\nPress 'a' to use array\nPress 'v' to use vector\n";
    char struct_type;
    cin >> struct_type;
    if (struct_type == 'a') interacter_array();
    if (struct_type == 'v') interacter_vector();
    if (struct_type == 'l') interacter_list();
    return;
}

void visual(){
    cout << "------VISUAL MODE------\n";
    IP temp = IP();
    cout << "Using array:\n";
    Array adress = Array();
    cout << "Adding '8.8.8.8' to head\n";
    Sleep(sleep_time);
    temp = IP("8.8.8.8");
    adress.append_left(temp);
    cout << "Printing all elemrnts\n";
    Sleep(sleep_time);
    adress.print();
    Sleep(sleep_time);
    cout << "Adding '255.255.255.0' to tail\n";
    Sleep(sleep_time);
    temp = IP("255.255.255.0");
    adress.append_right(temp);
    cout << "Printing all elemrnts\n";
    Sleep(sleep_time);
    adress.print();
    Sleep(sleep_time);
    cout << "Adding '255.0.0.0' to head\n";
    Sleep(sleep_time);
    temp = IP("255.0.0.0");
    adress.append_left(temp);
    cout << "Printing all elemrnts\n";
    Sleep(sleep_time);
    adress.print();
    Sleep(sleep_time);
    cout << "Adding '0.0.0.0' to head\n";
    Sleep(sleep_time);
    temp = IP("0.0.0.0");
    adress.append_left(temp);
    cout << "Printing all elemrnts\n";
    Sleep(sleep_time);
    adress.print();
    Sleep(sleep_time);
    cout << "Deleting element from tail\n";
    adress.pop_right();
    Sleep(sleep_time);
    cout << "Printing all elemrnts\n";
    Sleep(sleep_time);
    adress.print();
    Sleep(sleep_time);
    cout << "Using vector:\n";
    Vector adress_vector = Vector();
    cout << "Adding '8.8.8.8' to head\n";
    Sleep(sleep_time);
    temp = IP("8.8.8.8");
    adress_vector.append_left(temp);
    cout << "Printing all elemrnts\n";
    Sleep(sleep_time);
    adress_vector.print();
    Sleep(sleep_time);
    cout << "Adding '255.255.255.0' to tail\n";
    Sleep(sleep_time);
    temp = IP("255.255.255.0");
    adress_vector.append_right(temp);
    cout << "Printing all elemrnts\n";
    Sleep(sleep_time);
    adress_vector.print();
    Sleep(sleep_time);
    cout << "Adding '255.0.0.0' to head\n";
    Sleep(sleep_time);
    temp = IP("255.0.0.0");
    adress_vector.append_left(temp);
    cout << "Printing all elemrnts\n";
    Sleep(sleep_time);
    adress_vector.print();
    Sleep(sleep_time);
    cout << "Adding '0.0.0.0' to head\n";
    Sleep(sleep_time);
    temp = IP("0.0.0.0");
    adress_vector.append_left(temp);
    cout << "Printing all elemrnts\n";
    Sleep(sleep_time);
    adress_vector.print();
    Sleep(sleep_time);
    cout << "Deleting element from tail\n";
    adress_vector.pop_right();
    Sleep(sleep_time);
    cout << "Printing all elemrnts\n";
    Sleep(sleep_time);
    adress_vector.print();
    Sleep(sleep_time);
    cout << "Using list:\n";
    List adress_list = List();
    cout << "Adding '8.8.8.8' to head\n";
    Sleep(sleep_time);
    temp = IP("8.8.8.8");
    adress_list.append_left(temp);
    cout << "Printing all elemrnts\n";
    Sleep(sleep_time);
    adress_list.print();
    Sleep(sleep_time);
    cout << "Adding '255.255.255.0' to tail\n";
    Sleep(sleep_time);
    temp = IP("255.255.255.0");
    adress_list.append_right(temp);
    cout << "Printing all elemrnts\n";
    Sleep(sleep_time);
    adress_list.print();
    Sleep(sleep_time);
    cout << "Adding '255.0.0.0' to head\n";
    Sleep(sleep_time);
    temp = IP("255.0.0.0");
    adress_list.append_left(temp);
    cout << "Printing all elemrnts\n";
    Sleep(sleep_time);
    adress_list.print();
    Sleep(sleep_time);
    cout << "Adding '0.0.0.0' to head\n";
    Sleep(sleep_time);
    temp = IP("0.0.0.0");
    adress_list.append_left(temp);
    cout << "Printing all elemrnts\n";
    Sleep(sleep_time);
    adress_list.print();
    Sleep(sleep_time);
    cout << "Deleting element from tail\n";
    adress_list.pop_right();
    Sleep(sleep_time);
    cout << "Printing all elemrnts\n";
    Sleep(sleep_time);
    adress_list.print();
    Sleep(sleep_time);
    cout << "Have a nice day!\n";
}

void benchmark(){
    cout << "For List:\n";
    List list = List();
    double duration = 0.0;
    long long cnt_of_operations = 1;
    int start_time;
    cout << "   Time of adding:\n";
    while(duration < 1) {
        cnt_of_operations *=5;
        IP temp;
        start_time = clock();
        for (int i = 0; i < cnt_of_operations; i++) {
            temp.random_value();
            list.append_left(temp);
        }
        duration = (clock() - start_time) / 1000.0;
        cout << "      " << cnt_of_operations << " elements:" << duration << "\n";
    }
    long long etalon = cnt_of_operations;
    while(duration < 5) {
        cnt_of_operations += etalon;
        IP temp;
        start_time = clock();
        for (int i = 0; i < cnt_of_operations; i++) {
            temp.random_value();
            list.append_left(temp);
        }
        duration = (clock() - start_time) / 1000.0;
        cout  << "      " << cnt_of_operations << " elements:" << duration << "\n";
    }
    cout << "  Time of deleting\n";
    cnt_of_operations = 1;
    duration =  0;
    while(duration < 1 && !list.is_empty()) {
        cnt_of_operations = cnt_of_operations*5;
        start_time = clock();
        for (int i = 0; i < cnt_of_operations; i++) {
            list.pop_left();
        }
        duration = (clock() - start_time) / 1000.0;
        cout << "      " << cnt_of_operations << " elements:" << duration << "\n";
    }
    etalon = cnt_of_operations;
    while(duration < 5 && !list.is_empty()) {
        cnt_of_operations += etalon;
        start_time = clock();
        for (int i = 0; i < cnt_of_operations; i++) {
            list.pop_left();
        }
        duration = (clock() - start_time) / 1000.0;
        cout << "      " << cnt_of_operations << " elements:" << duration << "\n";
    }
    cout << "For Vector:\n";
    Vector vec = Vector();
    duration = 0.0;
    cnt_of_operations = 1;
    cout << "   Time of adding:\n";
    while(duration < 1) {
        cnt_of_operations *=5;
        IP temp;
        start_time = clock();
        for (int i = 0; i < cnt_of_operations; i++) {
            temp.random_value();
            vec.append_left(temp);
        }
        duration = (clock() - start_time) / 1000.0;
        cout << "      " << cnt_of_operations << " elements:" << duration << "\n";
    }
    etalon = cnt_of_operations;
    while(duration < 5) {
        cnt_of_operations += etalon;
        IP temp;
        start_time = clock();
        for (int i = 0; i < cnt_of_operations; i++) {
            temp.random_value();
            vec.append_left(temp);
        }
        duration = (clock() - start_time) / 1000.0;
        cout  << "      " << cnt_of_operations << " elements:" << duration << "\n";
    }
    cout << "  Time of deleting\n";
    cnt_of_operations = 1;
    duration =  0;
    while(duration < 1 && !vec.is_empty()) {
        cnt_of_operations = cnt_of_operations*5;
        start_time = clock();
        for (int i = 0; i < cnt_of_operations; i++) {
            vec.pop_right();
        }
        duration = (clock() - start_time) / 1000.0;
        cout << "      " << cnt_of_operations << " elements:" << duration << "\n";
    }
    etalon = cnt_of_operations;
    while(duration < 5 && !vec.is_empty()) {
        cnt_of_operations += etalon;
        start_time = clock();
        for (int i = 0; i < cnt_of_operations; i++) {
            vec.pop_right();
        }
        duration = (clock() - start_time) / 1000.0;
        cout << "      " << cnt_of_operations << " elements:" << duration << "\n";
    }
    cout << "For Array:\n";
    Array arr = Array();
    duration = 0.0;
    cnt_of_operations = 1;
    cout << "   Time of adding:\n";
    while(duration < 1) {
        cnt_of_operations *=5;
        if (cnt_of_operations > nmax) break;
        IP temp;
        start_time = clock();
        for (int i = 0; i < cnt_of_operations; i++) {
            temp.random_value();
            arr.append_left(temp);
        }
        duration = (clock() - start_time) / 1000.0;
        cout << "      " << cnt_of_operations << " elements:" << duration << "\n";
    }
    etalon = cnt_of_operations;
    while(duration < 5) {
        cnt_of_operations += etalon;
        if (cnt_of_operations >= nmax) break;
        IP temp;
        start_time = clock();
        for (int i = 0; i < cnt_of_operations; i++) {
            temp.random_value();
            arr.append_left(temp);
        }
        duration = (clock() - start_time) / 1000.0;
        cout  << "      " << cnt_of_operations << " elements:" << duration << "\n";
    }
    cout << "  Time of deleting\n";
    cnt_of_operations = 1;
    duration =  0;
    while(duration < 1 && !arr.is_empty()) {
        cnt_of_operations = cnt_of_operations*5;
        start_time = clock();
        for (int i = 0; i < cnt_of_operations; i++) {
            arr.pop_left();
        }
        duration = (clock() - start_time) / 1000.0;
        cout << "      " << cnt_of_operations << " elements:" << duration << "\n";
    }
    etalon = cnt_of_operations;
    while(duration < 5 && !arr.is_empty()) {
        cnt_of_operations += etalon;
        start_time = clock();
        for (int i = 0; i < cnt_of_operations; i++) {
            arr.pop_left();
        }
        duration = (clock() - start_time) / 1000.0;
        cout << "      " << cnt_of_operations << " elements:" << duration << "\n";
    }
}

void selector(){
    while (1){
        cout << "Choose mode:\nPress 'i' to interacter mod\nPress 'v' to visual mod\nPress 'b' to benchmark mod\nPress q to exit\n";
        char mod;
        cin >> mod;
        if (mod == 'q') break;
        if (mod == 'i') interacter();
        if (mod == 'v') visual();
        if (mod == 'b') benchmark();
    }
}

int main()
{
    srand(time(0));
    selector();
    return 0;
}
