#include <iostream>
#include <vector>

using std::cout;
using std::cin;
using std::vector;
using std::string;

typedef unsigned long long ll;

const ll MOD = 1e9 + 7;
const int MAX_POW = 1e6;
const int PRIME = 37;

int sqrt_complexity(string s, string t){// sqrt complexity
    for (int i = 0; i < s.size(); ++i)
        if (i + t.size() <= s.size()) {
            bool same = true;
            for (int j = 0; j < t.size(); ++j)
                if (s[i + j] != t[j]) {
                    same = false;
                    break;
                }
            if (same){
                return i + 1;
            }
        }
    return -1;
}

//begin of Rabina-Karpa algo

vector <ll> prime_pow(){
    vector <ll> result;
    result.resize(MAX_POW + 1);
    result[0] = 1;
    for (int i = 1; i <= MAX_POW; ++i)
        result[i] = (result[i - 1]  * PRIME) % MOD;
    return result;
}

vector <ll> hash(string s, vector <ll> prime_pow){
    vector <ll> result;
    result.resize(s.size() + 1);
    result[0] = 0;
    for (int i = 0; i < s.size(); ++i)
        result[i + 1] = ((((s[i] - 'a') * prime_pow[i + 1] + MOD) % MOD) +  result[i] + MOD) % MOD;
    return result;
}

ll get_hash(vector <ll> &hash_of_string, int l, int r, vector <ll> &prime_pow){
    return ((hash_of_string[r] - hash_of_string[l - 1]) * prime_pow[MAX_POW - r] + MOD) % MOD;
}
/*
bool compare_hash(vector <ll> &hash_1, vector <ll> &hash_2, int l1, int r1, int l2, int r2, vector <ll> &prime_pow){
    return get_hash(hash_1, l1, r1, prime_pow) == get_hash(hash_2, l2, r2, prime_pow);
}*/

int find_string(string s, string t){
    vector <ll> primes = prime_pow();
    vector <ll> s_hash = hash(s, primes);
    vector <ll> t_hash = hash(t, primes);
    ll hash_for_comparing = get_hash(t_hash, 1, t.size(), primes);
    for (int i = 1; i <= s.size(); ++i)
        if (i + t.size() - 1 <= s.size()) {
            if (get_hash(s_hash, i, i + t.size() - 1, primes) == hash_for_comparing)
                return i;
        }
    return -1;
}

//end of Rabina-Karpa

int main() {
    string s, t;
    cin >> s >> t;
    cout << sqrt_complexity(s, t);
    return 0;
}