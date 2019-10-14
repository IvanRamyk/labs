#include <iostream>
#include <vector>
#include <algorithm>

using std::cout;
using std::cin;
using std::vector;

struct bolt{
    int size;
};

struct nut{
    int size;
};

bool operator <(bolt b, nut n){ return b.size < n.size; }
bool operator >(bolt b, nut n){ return b.size > n.size; }
bool operator ==(bolt b, nut n){ return b.size == n.size; }

void get(int &n, vector <bolt> &bolts, vector <nut> &nuts){
    cout << "Please, enter number of bolts and nuts\n";
    cin >> n;
    bolts.resize(n);
    nuts.resize(n);
    cout << "Please, enter bolts' sizes\n";
    for (int i = 0; i < n; ++i)
        cin >> bolts[i].size;
    cout << "Please, enter nuts' sizes\n";
    for (int i = 0; i < n; ++i)
        cin >> nuts[i].size;
}

int get_nut_pos(bolt b, vector <nut> nuts, int l, int r){
    for (int i = l; i <= r; ++i)
        if (b == nuts[i])
            return i;
    return -1;
}

int get_bolt_pos(nut n, vector <bolt> bolts, int l, int r){
    for (int i = l; i <= r; ++i)
        if (bolts[i] == n)
            return i;
    return -1;
}

bool quick_sort(std::vector <bolt> &bolts, vector <nut> &nuts, int l = 0, int r = -1){
    //cout << "lr "<< l << " " << r << "\n";
    if (r == -1)
        r = bolts.size() - 1;
    if (l >= r) return true;
    int i = l;
    int j = r;
    int pos_bolt = (l + r) / 2;
    int pos_nut = get_nut_pos(bolts[(l + r) / 2],nuts, l, r);
    if (pos_nut == -1) {
        cout << bolts[pos_bolt].size << " " << l << "  " << r << "\n";
        return false;
    }
    int pos = l;
    for (int k = l; k <= r; ++k)
        if (bolts[pos_bolt] > nuts[k])
            ++pos;
    std::swap(bolts[pos_bolt], bolts[pos]);
    std::swap(nuts[pos_nut], nuts[pos]);
    i = l;
    j = r;
    while (i < pos){
        while (i < pos && bolts[i] < nuts[pos])
            ++i;
        if (i < pos){
            while (bolts[j] > nuts[pos])
                --j;
            std::swap(bolts[i], bolts[j]);
        }
    }
    i = l;
    j = r;
    while (i < pos){
        while (i < pos && bolts[pos] > nuts[i])
            ++i;
        if (i < pos){
            while (bolts[pos] < nuts[j])
                --j;
            std::swap(nuts[i], nuts[j]);
        }
    }
    //std::cout << l << " "  << r << " " << pos << "\n";
    if (!quick_sort(bolts, nuts, l, pos))
        return false;
    return quick_sort(bolts, nuts, pos + 1, r);
}

void print(vector <bolt> bolts, vector <nut> nuts){
    for (int i = 0; i < bolts.size(); ++i){
        cout << "Bolt size: " << bolts[i].size << " ";
        cout << "Nut size: " << nuts[i].size << "\n";
    }
    cout << "Ou, e\n";
}

void rand_mas(int n, vector <bolt> &bolts, vector <nut> &nuts){
    bolts.resize(n);
    nuts.resize(n);
    for (int i = 0; i < n; ++i) {
        bolts[i].size = i;
        nuts[i].size = i;
    }
    std::random_shuffle(bolts.begin(), bolts.end());
    std::random_shuffle(nuts.begin(), nuts.end());
    for (auto i : bolts){
        cout << i.size << " ";
    }
    cout << "\n";
    for (auto i : nuts){
        cout << i.size << " ";
    }
}


int main() {
    vector <bolt> bolts;
    vector <nut> nuts;
    int n;
    cin >> n;
    //get(n, bolts, nuts);
    rand_mas(n, bolts, nuts);
    if(!quick_sort(bolts, nuts)){
        cout << "Invalid sizes\n";
        return 0;
    }
    print(bolts, nuts);
    return 0;
}