#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>


using namespace std;

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
        cout << name << " " << amount << " of " << units << "\n";
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
};

int main()
{
    File str;
    /*int n;
    cin >> n;
    for (int i = 1; i <= n; ++i)
        str.get();*/
    str.print();
    return 0;
}
