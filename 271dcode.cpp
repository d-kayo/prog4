#include <bits/stdc++.h>
using namespace std;

typedef unsigned long long ull;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    string s;
    cin >> s;
    int n = s.size();

    string good;
    cin >> good;

    int k;
    cin >> k;

    vector<int> bad(n);
    for (int i = 0; i < n; i++)
        bad[i] = (good[s[i] - 'a'] == '0');

    const ull base = 1315423911ULL;
    const ull mod1 = 1000000007ULL;
    const ull mod2 = 1000000009ULL;

    vector<ull> p1(n + 1, 1), p2(n + 1, 1);
    for (int i = 1; i <= n; i++) {
        p1[i] = (p1[i - 1] * base) % mod1;
        p2[i] = (p2[i - 1] * base) % mod2;
    }

    vector<ull> h1(n + 1, 0), h2(n + 1, 0);
    for (int i = 0; i < n; i++) {
        h1[i + 1] = (h1[i] * base + s[i]) % mod1;
        h2[i + 1] = (h2[i] * base + s[i]) % mod2;
    }

    auto getHash = [&](int l, int r) {  
        ull x1 = (h1[r + 1] + mod1 - (h1[l] * p1[r - l + 1]) % mod1) % mod1;
        ull x2 = (h2[r + 1] + mod2 - (h2[l] * p2[r - l + 1]) % mod2) % mod2;
        return (x1 << 32) ^ x2;  
    };

    unordered_set<ull> seen;

    for (int i = 0; i < n; i++) {
        int badCount = 0;

        for (int j = i; j < n; j++) {
            badCount += bad[j];
            if (badCount > k) break;

            ull hashVal = getHash(i, j);
            seen.insert(hashVal);
        }
    }

    cout << seen.size() << "\n";
    return 0;
}
