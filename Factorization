#include <bits/stdc++.h>

using namespace std;

const int max_divisior = 110;

void generate_divisiors(int smallest_divisior[], int n){
    for (int i = 2; i <= n; ++i)
        if (!smallest_divisior[i]){
            smallest_divisior[i] = i;
            for (int j = 2; i * j <= n; ++j)
                if (!smallest_divisior[i * j]) smallest_divisior[i * j] = i;
        }
}

void add_factor(int factor[], int smallest_divisior[], int k){
    while (k != 1){
        factor[smallest_divisior[k]]++;
        k /= smallest_divisior[k];
    }
}

void print_factor(int factor[], int n){
    cout << n << "! = ";
    bool f = 0;
    for (int i = 2; i <= n; ++i)
        if (factor[i]){
            if (f) cout << " * ";
            f = 1;
            cout << i << "^" << factor[i];
        }
    if (!f) cout << 1;
    cout << "\n";
}

int main()
{
    int n, factor[max_divisior], smallest_divisior[max_divisior];
    cin >> n;
    for (int i = 1; i <= n; ++i)
        factor[i] = 0;
    for (int i = 1; i <= n; ++i)
        smallest_divisior[i] = 0;
    generate_divisiors(smallest_divisior, n);
    for (int i = 2; i <= n; ++i)
        add_factor(factor, smallest_divisior, i);
    print_factor(factor, n);
    return 0;
}
