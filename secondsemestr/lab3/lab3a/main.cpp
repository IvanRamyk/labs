#include <iostream>
#include <ctime>
#include <stdio.h>
#include <time.h>
#include <windows.h>
#include <chrono>

using namespace std;

int bubble_size = 10;
bool is_demo = 0;
int n;
const int sleep_const = 2 * 1000;

struct Date{
    int year;
    int month;
    int day;
    int hour;
    int minute;
    int value(){
        return ((((year * 12) + month) * 31 + day) + hour) * 60 + minute;
    }
    void init(){
        year = rand() % 3000 + 1;
        month = rand() % 12 + 1;
        day = rand() % 31 + 1;
        hour = rand() % 24;
        minute = rand() % 60;
    }
    void print(){
        printf("%d.%02d.%02d %02d:%02d\n", year, month, day, hour, minute);
    }
};
bool operator <(Date a, Date b){
     return a.value() > b.value();
 }
bool operator >(Date a, Date b){
    return a.value() < b.value();
 }
void bubble_sort(Date array[], int number_of_elements){
     bool not_sort = 1;
     while (not_sort){
         not_sort = 0;
         for (int i = 0; i < number_of_elements - 1; ++i)
             if (array[i + 1] < array[i]) {
                 swap(array[i], array[i + 1]);
                 not_sort = 1;
             }
         for (int i = number_of_elements - 2; i >= 0; --i)
             if (array[i + 1] < array[i])
                 swap(array[i], array[i + 1]);
     }
 }
void bubble_sort(Date array[], int left, int rigth){
    bool not_sort = 1;
    while (not_sort){
        not_sort = 0;
        for (int i = left; i < rigth; ++i)
            if (array[i + 1] < array[i]) {
                swap(array[i], array[i + 1]);
                not_sort = 1;
            }
        for (int i = rigth - 1; i >= left; --i)
            if (array[i + 1] < array[i])
                swap(array[i], array[i + 1]);
        if (is_demo) {
            for (int i = 0; i < n; ++i)
                array[i].print();
            cout << "=======\n";
            Sleep(sleep_const);
        }
    }
}

int partition(Date array[], int left, int right){
     Date pivot = array[(left + right) >> 1];
     int i = left, j = right;
     while(1){
         while (array[i] < pivot)
             ++i;
         while (array[j] > pivot)
             j--;
         if (i >= j) return j;
        swap(array[i], array[j]);
        i++,j--;
     }
}//Hoare

void quick_sort(Date array[], int left, int right){
     if (left < right){
         int middle = partition(array, left, right);
         //middle = (left + right) / 2;
         quick_sort(array, left, middle - 1);
         quick_sort(array, middle + 1, right);
         if (is_demo) {
             for (int i = 0; i < n; ++i)
                 array[i].print();
             cout << "=======\n";
             Sleep(sleep_const);
         }
     }
 }

void merge(Date array[], int left, int middle, int right){
     Date temp [right + 1];
     int i = left;
     int j = middle + 1;
     int k = left;
     while (k != right + 1){
         if (i == middle + 1){
             temp[k] = array[j];
             ++j;
         }
         else if (j == right + 1){
             temp[k] = array[i];
             ++i;
         }
         else if (array[i] > array[j]){
             temp[k] = array[j];
             ++j;
         }
         else {
             temp[k] = array[i];
             ++i;
         }
         ++k;
     }
     for (int i = left; i <= right; ++i)
         array[i] = temp[i];
 }

void merge_sort(Date array[], int left, int right){
     if (left < right) {
         //cout << left << " " << right << "\n";
         int middle = (left + right) >> 1;
         merge_sort(array, left, middle);
         merge_sort(array, middle + 1, right);
         merge(array, left, middle, right);
         //cout << left << " " << right << " done!\n";
         if (is_demo) {
             for (int i = 0; i < n; ++i)
                 array[i].print();
             cout << "=======\n";
             Sleep(sleep_const);
         }
     }
 }

void combine_merge_bubble_sort(Date array[], int left, int right)
{
    if (right - left > bubble_size) {
        int middle = (left + right) >> 1;
        merge_sort(array, left, middle);
        merge_sort(array, middle + 1, right);
        merge(array, left, middle, right);
    }
    bubble_sort(array, left, right);
    if (is_demo) {
        for (int i = 0; i < n; ++i)
            array[i].print();
        cout << "=======\n";
        Sleep(sleep_const);
    }
}

void demo(){
    srand(time(0));
    is_demo = 1;
    Date arr[1000];
    cout << "Please enter size of array\n";
    cin >> n;
    for (int i = 0; i < n; ++i)
        arr[i].init();
    cout << "Array:\n";
    Sleep(sleep_const);
    for (int i = 0; i < n; ++i)
        arr[i].print();
    Sleep(sleep_const);
    Date arr1 [1000];
    for (int i = 0; i < n; ++i)
        arr1[i] = arr[i];
    cout << "Sorting with bubble sort:\n";
    Sleep(sleep_const);
    bubble_sort(arr1, 0, n - 1);
    for (int i = 0; i < n; ++i)
        arr1[i] = arr[i];
    cout << "Sorting with quick sort:\n";
    Sleep(sleep_const);
    quick_sort(arr1, 0, n - 1);
    for (int i = 0; i < n; ++i)
        arr1[i] = arr[i];
    cout << "Sorting with merge sort:\n";
    Sleep(sleep_const);
    merge_sort(arr1, 0, n - 1);
    for (int i = 0; i < n; ++i)
        arr1[i] = arr[i];
    cout << "Sorting with combine sort:\n";
    Sleep(sleep_const);
    combine_merge_bubble_sort(arr1, 0, n - 1);
}

void selector(){
     cout << "Press 'd' to demo mod\n";
     char mode;
     cin >> mode;
     if (mode == 'd'){
         demo();
     }
}

int main() {
     selector();
     return 0;
}
