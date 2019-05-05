#include <iostream>
#include <vector>
#include <algorithm>


using namespace std;

struct Date{
    int year;
    int month;
    int day;
    void print(){
        cout << day << "." << month << "." << year << "\n";
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
        cout << name << " " << amount << " of " << units << "\n";
        cout << "produced ";
        date.print();
        time.print();
        cout << "shelf life - " << shelf_life << "\n";
    }
    void get(){

    }
};

struct Vector{
    vector <Product> products;
    void get(Product temp){
        temp.id = products.size();
        products.push_back(temp);
    }
    void print(){
        for (auto i : products)
            i.print();
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
    void get(Product temp){
        freopen("struct", "r", stdin);
        vector <Product> temp;
        Product product;
        while ()
    }
};

int main()
{

    return 0;
}
