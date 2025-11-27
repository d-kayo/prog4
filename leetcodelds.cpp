#include <bits/stdc++.h>
using namespace std;

string longestDupSubstring(string s) {
    int n = s.size();
    vector<long long> power(n+1);
    const long long base = 1315423911LL; 
    const long long mod  = (1LL << 61) - 1; 

    auto modmul = [&](long long a, long long b) {
        __int128 t = (__int128)a * b;
        t = (t >> 61) + (t & mod);
        if (t >= mod) t -= mod;
        return (long long)t;
    };

    auto modadd = [&](long long a, long long b) {
        long long r = a + b;
        if (r >= mod) r -= mod;
        return r;
    };

    power[0] = 1;
    for (int i = 1; i <= n; ++i) 
        power[i] = modmul(power[i-1], base);

    vector<long long> hashv(n+1, 0);
    for (int i = 0; i < n; ++i) {
        hashv[i+1] = modadd(modmul(hashv[i], base), s[i]);
    }

    auto getHash = [&](int l, int r) {
        long long h = hashv[r] - modmul(hashv[l], power[r-l]);
        if (h < 0) h += mod;
        return h;
    };

    auto check = [&](int L) -> int {
        if (L == 0) return -1;
        unordered_map<long long, vector<int>> mp;
        mp.reserve(n);
        for (int i = 0; i + L <= n; ++i) {
            long long h = getHash(i, i + L);
            auto &vec = mp[h];
            for (int start : vec) {
                if (s.compare(start, L, s, i, L) == 0)
                    return i; 
            }
            vec.push_back(i);
        }
        return -1;
    };

    int left = 1, right = n - 1;
    int bestStart = -1, bestLen = 0;

    while (left <= right) {
        int mid = (left + right) / 2;
        int pos = check(mid);
        if (pos != -1) {
            bestStart = pos;
            bestLen = mid;
            left = mid + 1;  
        } else {
            right = mid - 1; 
        }
    }

    return (bestStart == -1 ? "" : s.substr(bestStart, bestLen));
}

int main() {
    string s;
    cin >> s;
    cout << longestDupSubstring(s) << endl;
}
