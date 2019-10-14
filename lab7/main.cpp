#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::vector;
using std::string;

typedef unsigned long long ll;

const ll MOD = 1e9 + 7;
const int MAX_POW = 1e6;
const int PRIME = 37;
const int SIZE = 100;

vector <ll> prime_pow(){
    vector <ll> result;
    result.resize(MAX_POW + 1);
    result[0] = 1;
    for (int i = 1; i <= MAX_POW; ++i)
        result[i] = (result[i - 1]  * PRIME) % MOD;
    return result;
}

vector <vector <ll>> hash(vector<string> s, vector <ll> prime_pow){
    vector<vector <ll>> result;
    result.resize(s.size() + 1);
    for (int i = 0; i < result.size(); ++i)
        result[i].resize(result.size());
    result[0][0] = 0;
    for (int i = 0; i < s.size() ; ++i)
        for (int j = 0; j < s[i].size(); ++j) {
            result[i + 1][j + 1] = ((((s[i][j] - 'a') * prime_pow[(i) * SIZE + (j + 1)] + MOD * MOD) % MOD) +
                                    result[i][j + 1] + result[i + 1][j] - result[i][j] + MOD) % MOD;
            //cout << i + 1 << " " << j + 1 << " " << (((s[i][j] - 'a') * prime_pow[(i) * SIZE + (j + 1)] + MOD) % MOD) << "\n";
        }
    return result;
}

void print(vector <vector<ll>> hash){
    for (auto i : hash) {
        for (auto j : i)
            cout << j << " ";
        cout << "\n";
    }
}

ll get_hash(vector<vector <ll>> &hash_of_string, int x1, int y1, int x2, int y2, vector <ll> &prime_pow){
    //cout << x1 << y1 <<" "<< x2 << y2 <<" " << hash_of_string.size() << "\n";
    //print(hash_of_string);
    //for (int i = 0; i < )
    return (((hash_of_string[x2][y2] - hash_of_string[x2][y1 - 1] - hash_of_string[x1 - 1][y2]  +
    hash_of_string[x1 - 1][y1 - 1] + MOD) % MOD)  * prime_pow[MAX_POW - y2 - (x2-1) * SIZE ] + MOD *  MOD) % MOD;
}

bool compare_hash(vector <vector <ll> > &hash_1, vector <vector <ll>> &hash_2, int first_x1, int first_y1, int first_x2, int first_y2, int second_x1,
        int second_y1, int second_x2, int second_y2, vector <ll> &prime_pow){
    //cout << get_hash(hash_1, first_x1, first_y1, first_x2, first_y2, prime_pow) << " " <<  get_hash(hash_2, second_x1, second_y1, second_x2, second_y2, prime_pow) << "\n";
    return get_hash(hash_1, first_x1, first_y1, first_x2, first_y2, prime_pow) == get_hash(hash_2, second_x1, second_y1, second_x2, second_y2, prime_pow);
}


void print_string(vector <string > hash){
    for (auto i : hash)
        cout << i << "\n";
}

bool check(vector<string> &s1, vector<string> &s2){
    //print_string(s1);
    //print_string(s2);
    //size = s1.size();
    vector <ll> primes = prime_pow();
    vector<vector <ll>> hash_1 = hash(s1, primes);
    vector<vector <ll>> hash_2 = hash(s2, primes);
    print(hash_1);
    print(hash_2);
    for (int i = 1; i <= s1.size(); ++i)
        for (int j = 1; j <= s1.size(); ++j)
            if (i + s2.size() - 1 <= s1.size() && j + s2.size() - 1  <= s1.size()) {
                //cout << i <<  " " << j << "\n";
                //cout << hash_1.size() << " " << hash_2.size() << "\n";
                if (compare_hash(hash_1, hash_2, i, j, i + s2.size() - 1, j + s2.size() - 1, 1, 1, s2.size(), s2.size(),
                                 primes))
                    return true;
            }
    return false;
}
vector <string> get_string() {
    vector <string> res;
    int n;
    cin >> n;
    res.resize(n);
    for (int i = 0; i < n; ++i)
        cin >> res[i];
    return res;
}

int main() {
    vector <string> s1 = get_string(), s2 = get_string();
    if (check(s1, s2))
        cout << "YES";
    else
        cout << "NO";
    return 0;
}