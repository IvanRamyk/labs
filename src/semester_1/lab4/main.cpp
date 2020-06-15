#include <iostream>
#include <vector>

using std::cout;
using std::cin;
using std::vector;

struct object{
    int key;
    int data;
};

vector <object> get_data(){
    vector <object> data;
    cout << "Please, enter number of objects\n";
    int n;
    cin >> n;
    data.resize(n);
    for (int i = 0; i < n; ++i){
        cout << "Enter key\n";
        cin >> data[i].key;
        cout << "Enter data\n";
        cin >> data[i].data;
    }
    return data;
}

void counting_sort(vector <object> &data){// time complexity O(n), stable
    vector <object> result;
    result.resize(data.size());
    int last_zero_position = - 1;
    int cnt_one = 0;
    for (int i = 0; i < data.size(); ++i){
        if (data[i].key == 0)
            ++last_zero_position;
        else
            ++cnt_one;
    }
    int last_one_position = last_zero_position + cnt_one;
    for (int i = data.size() - 1; i >= 0; --i)
        if (data[i].key == 1)
            result[last_one_position--] = data[i];
        else
            result[last_zero_position--] = data[i];
    data = result;
}

void bubble_sort(vector<object> &data){// stable, extra memory O(1)
    for (int i = 0; i < data.size(); ++i)
        for (int j = 0; j < data.size() - 1; ++j)
            if (data[i].key > data[i + 1].key)
                std::swap(data[i], data[i + 1]);
}

void my_sort(vector <object> &data){// time complexity O(n), extra memory O(1)
    int last_zero_position = - 1;
    for (int i = 0; i < data.size(); ++i)
        if (data[i].key == 0)
            ++last_zero_position;
    int pos = -1;
    for (int i = 0; i < data.size(); ++i)
        if (data[i].key == 0){
            pos = i;
            break;
        }
    if (pos == -1) return;
    std::swap(data[pos], data[last_zero_position]);
    int i = 0;
    int j = last_zero_position + 1;
    while (i < last_zero_position) {
        while (i < last_zero_position && data[i].key == 0)
            ++i;
        if (i != last_zero_position) {
            while (data[j].key == 1)
                ++j;
            std::swap(data[i], data[j]);
        }
    }
}

void print(vector <object> data){
    for (int i = 0; i < data.size(); ++i)
        cout << "Key: " << data[i].key << " Data: " << data[i].data << "\n";
}

vector<object> random_data(){
    vector <object> data;
    cout << "Please, enter number of objects\n";
    int n;
    cin >> n;
    data.resize(n);
    for (int i = 0; i < n; ++i){
        data[i].key = rand() % 2;
        data[i].data = rand();
    }
    return data;
}

void demo(){
    cout << "Enter 'y' if you want to use random data\n";
    char answer;
    cin >> answer;
    vector <object> data;
    if (answer == 'y')
        data = random_data();
    else
        data = get_data();
    cout << "Enter number of sort which you want to use\n";
    int type;
    cin >> type;
    if (type == 1)
        counting_sort(data);
    if (type == 2)
        bubble_sort(data);
    if (type == 3)
        my_sort(data);
    print(data);
}

int main() {
    srand(time(0));
    demo();
    return 0;
}