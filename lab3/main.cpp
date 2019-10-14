#include <iostream>

using std::cin;
using std::cout;
using std::swap;

const int MAX_SIZE = 100100;
const int CNT_SONS = 1000;


int heap[MAX_SIZE];
int heap_size = 0;

int parent(int v){
    return (v - 1) / CNT_SONS;
}

int son(int v, int number){
    return v * CNT_SONS + 1 + number;
}

void siftUp(int v){
    while (v > 0 && heap[parent(v)] < heap[v]){
        swap(heap[v], heap[parent(v)]);
        v = parent(v);
    }
}

void siftDown(int v){
    while (son(v, 0) < heap_size){
        int max_son = son(v, 0);
        for (int i = 1; i < CNT_SONS; ++i)
            if (son(v, i) < heap_size && heap[son(v, i)] > heap[max_son])
                max_son = son(v, i);
        if (heap[v] < heap[max_son]){
            swap(heap[v], heap[max_son]);
            v = max_son;
        }
        else
            break;
    }
}

void increaseKey(int v, int d){
    heap[v] += d;
    if (d < 0)
        siftDown(v);
    else
        siftUp(v);
}

void insert(int data){
    heap[heap_size] = data;
    ++heap_size;
    siftUp(heap_size - 1);
}

int top(){
    return heap[0];
}

void pop(){
    swap(heap[0], heap[heap_size - 1]);
    heap_size--;
    siftDown(0);
}

void print_heap(){
    for (int i = 0; i < heap_size; ++i)
        cout << heap[i] << " ";
    cout << "\n";
}

void insert_random_data(int n){
    for (int i = 0; i < n; ++i)
        insert(rand() % n);
}

int main() {
    srand(time(0));
    int n;
    cin >> n;
    insert_random_data(n);
    //print_heap();
    for (int i = 0; i < n; ++i){
        cout << top() << " ";
        pop();
        //print_heap();
    }
    return 0;
}