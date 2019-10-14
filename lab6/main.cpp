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

bool compare_hash(vector <ll> &hash_1, vector <ll> &hash_2, int l1, int r1, int l2, int r2, vector <ll> &prime_pow){
    return get_hash(hash_1, l1, r1, prime_pow) == get_hash(hash_2, l2, r2, prime_pow);
}

bool is_cycle(string s1, string &s2){
    if (s1.size() != s2.size())
        return false;
    vector <ll> primes = prime_pow();
    s1 = s1 + s1;
    vector <ll> hash_1 = hash(s1, primes);
    vector <ll> hash_2 = hash(s2, primes);
    for (int i = 0; i < s1.size(); ++i){
        int l = i;
        int r = i + s2.size() - 1;
        if (compare_hash(hash_1, hash_2, l,r,0, s2.size(), primes))
            return true;
    }
    return false;
}

void test_all_permutations(string s){
    for (int i = 1; i < s.size(); ++i){
        string temp = "";
        for (int j = i; j != (i - 1); ++j, j %= s.size()){
            temp += s[j];
        }
        temp += s[i - 1];
        if (is_cycle(s, temp))
            cout << "YES\n";
    }
}

int main() {
    string s1, s2;
    cin >> s1 >> s2;
    test_all_permutations(s1);
    if (is_cycle(s1, s2))
        cout << "YES\n";
    else
        cout << "NO\n";
    return 0;
}