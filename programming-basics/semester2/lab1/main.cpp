#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <ctime>
#include <unistd.h>

using namespace std;
const int sleep_time = 1;

void ok(){
    cout << "OK\n";
}

struct Date{
    int year;
    int month;
    int day;
    void print(){
        cout << day << "." << month << "." << year << "\n";
    }
    void get(){
        cin >> day >> month >> year;
    }
    void in(ifstream fin){
        fin >> day >> month >> year;
    }
    void out(ofstream fout){
        fout << day << " " << month << " " << year << " ";
    }
};
bool operator <=(Date a, Date b){
    return (a.year * 100 + a.month) * 20 + a.day <= (b.year * 100 + b.month) * 20 + b.day;
}


struct Time{
    int hours;
    int minutes;
    void print(){
        cout << hours << ":" << minutes << "\n";
    }
    void get(ifstream fin){
        fin >> hours >> minutes;
    }
    void out(ofstream fout){
        fout << hours << " " << minutes << " ";
    }
};

struct Product{
    int id;
    string name;
    string units;
    int amount;
    Date date;
    Time time;
    int shelf_life;
    void print(){
        cout << name << " " << amount << " " << units << "\n";
        cout << "produced ";
        date.print();
        time.print();
        cout << "shelf life - " << shelf_life << "\n";
    }
    bool get(){
        cin >> name >> amount >> units;
        cin >> date.day >> date.month >> date.year;
        cin >> time.hours >> time.minutes;
        if (cin >> shelf_life) return 1;
        return 0;
    }
    bool in(ifstream& fin){
        fin >> name >> amount >> units;
        fin >> date.day >> date.month >> date.year;
        fin >> time.hours >> time.minutes;
        if (fin >> shelf_life) return 1;
        return 0;
    }
    void out(ofstream& fout){
        fout << name << " " << amount << " " << units << " ";
        fout << date.day << " " << date.month << " " << date.year << " ";
        fout << time.hours << " " << time.minutes << " ";
        fout << shelf_life << "\n";
    }
};

struct Vector{
    vector <Product> products;
    void get(){
        Product temp;
        temp.get();
        temp.id = products.size();
        products.push_back(temp);
    }
    void print(){
        for (auto i : products)
            i.print();
        cout << "\n\n";
    }
    vector <Product> search_end_name(string end){
        vector <Product> result;
        reverse(end.begin(), end.end());
        for (auto i : products)
            if (i.name.size() >= end.size()){
                bool is_same = 1;
                for (int j = 0; j < end.size(); ++j)
                    if (end[j] != i.name[i.name.size() - 1 - j])
                        is_same = 0;
                if (is_same) result.push_back(i);
            }
        return result;
    }
    vector <Product> search_units(string units_etalon, int life_etalon){
        vector <Product> result;
        for (auto i : products)
            if (units_etalon == i.units && i.shelf_life >= life_etalon)
                result.push_back(i);
        return result;
    }
    vector <Product> search_date(Date left, Date right){
        vector <Product> result;
        for (auto i : products)
            if (left <= i.date && i.date <= right)
                result.push_back(i);
        return result;
    }
    void del(int id){
        products.erase(products.begin() + id);
    }
};

struct File{
    void get(){
        Product to_ad;
        to_ad.get();
        string file = "struct";
        ifstream fin("struct");
        vector <Product> temp;
        Product product;
        while (product.in(fin))
            temp.push_back(product);
        fin.close();
        ofstream fout("struct");
        for (auto i : temp)
            i.out(fout);
        to_ad.out(fout);
        fout.close();
    }
    void print(){
        vector <Product> temp;
        Product product;
        ifstream fin("struct");
        while (product.in(fin))
            temp.push_back(product);
        fin.close();
        for (auto i : temp)
            i.print();
    }
    vector <Product> file_to_vector(){
        vector <Product> result;
        Product product;
        ifstream fin("struct");
        while (product.in(fin))
            result.push_back(product);
        fin.close();
        return result;
    }
    vector <Product> search_end_name(string end){
        vector <Product> result;
        reverse(end.begin(), end.end());
        vector <Product> products = file_to_vector();
        for (auto i : products)
            if (i.name.size() >= end.size()){
                bool is_same = 1;
                for (int j = 0; j < end.size(); ++j)
                    if (end[j] != i.name[i.name.size() - 1 - j])
                        is_same = 0;
                if (is_same) result.push_back(i);
            }
        return result;
    }
    vector <Product> search_units(string units_etalon, int life_etalon){
        vector <Product> result;
        vector <Product> products = file_to_vector();
        for (auto i : products)
            if (units_etalon == i.units && i.shelf_life >= life_etalon)
                result.push_back(i);
        return result;
    }
    vector <Product> search_date(Date left, Date right){
        vector <Product> result;
        vector <Product> products = file_to_vector();
        for (auto i : products)
            if (left <= i.date && i.date <= right)
                result.push_back(i);
        return result;
    }
};

void print_command_list(){
    cout << "In proggres..\n";
}

void vector_interacter(){
    Vector products;
    cout << "Press 'h' to view list of commands\n";
    while (1){
        string command_type;
        cin >> command_type;
        if (command_type == "q") break;
        if (command_type == "h") print_command_list();
        if (command_type == "add"){
            products.get();
            ok();
        }
        if (command_type == "print"){
            products.print();
        }
        if (command_type == "search_name"){
            string name;
            cin >> name;
            vector <Product> result = products.search_end_name(name);
            for (auto i : result)
                i.print();
        }
        if (command_type == "search_unit"){
            string unit; int life;
            cin >> unit >> life;
            vector <Product> result = products.search_units(unit, life);
            for (auto i : result)
                i.print();
        }
        if (command_type == "search_date"){
            Date left, right;
            left.get();
            right.get();
            vector <Product> result = products.search_date(left, right);
            for (auto i : result)
                i.print();
        }
    }
}

void file_interacter(){
    File products;
    cout << "Press 'h' to view list of commands\n";
    while (1){
        string command_type;
        cin >> command_type;
        if (command_type == "q") break;
        if (command_type == "h") print_command_list();
        if (command_type == "add"){
            products.get();
            ok();
        }
        if (command_type == "print"){
            products.print();
        }
        if (command_type == "search_name"){
            string name;
            cin >> name;
            vector <Product> result = products.search_end_name(name);
            for (auto i : result)
                i.print();
        }
        if (command_type == "search_unit"){
            string unit; int life;
            cin >> unit >> life;
            vector <Product> result = products.search_units(unit, life);
            for (auto i : result)
                i.print();
        }
        if (command_type == "search_date"){
            Date left, right;
            left.get();
            right.get();
            vector <Product> result = products.search_date(left, right);
            for (auto i : result)
                i.print();
        }
    }
}

void interacter(){
    cout << "-------INTERACTOR MODE-------\nChoose type of struct:\nPress 'r' to use RAM\nPress 'f' to use file\n";
    char struct_type;
    cin >> struct_type;
    if (struct_type == 'r') vector_interacter();
    if (struct_type == 'f') file_interacter();
    return;
}

void visual(){
    cout << "------VISUAL MODE------\n";
    cout << "Using vector:\n";
    Vector products;
    cout << "Adding water to struct\n";
    sleep(sleep_time);
    Product temp = {1, "water", "litrs",10, 12,10,2001,12,35,4000};
    products.products.push_back(temp);
    cout << "Printing all elemrnts\n";
    sleep(sleep_time);
    products.print();
    sleep(sleep_time);
    cout << "add tea\n";
    sleep(sleep_time);
    temp = {2, "tea", "kg", 5, 12,10,2001,12,35,4000};
    products.products.push_back(temp);
    cout << "Printing all elemrnts\n";
    sleep(sleep_time);
    products.print();
    sleep(sleep_time);
    cout << "Searching name ending 'r'\n";
    vector <Product> result = products.search_end_name("r");
    for (auto i : result)
        i.print();
    sleep(sleep_time);

    cout << "Using files:\n";
    File product;
    cout << "Adding water to struct\n";
    sleep(sleep_time);
    temp = {1, "water", "litrs",10, 12,10,2001,12,35,4000};
    cout << "Printing all elemrnts\n";
    sleep(sleep_time);
    products.print();
    sleep(sleep_time);
    cout << "add tea\n";
    sleep(sleep_time);
    temp = {2, "tea", "kg", 5, 12,10,2001,12,35,4000};

    cout << "Printing all elemrnts\n";
    sleep(sleep_time);
    products.print();
    sleep(sleep_time);
    cout << "Searching name ending 'a'\n";
    result = product.search_end_name("a");
    for (auto i : result)
        i.print();
    sleep(sleep_time);
    cout << "Have a nice day!\n";
}

void benchmark(){

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
    selector();
    return 0;
}
