#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    string s;
    if(!(cin >> s)) return 0;
    int n = (int)s.size();
    const int MAXN = 5000; 
    vector< bitset<MAXN> > pal(n);
    
    for (int i = 0; i < n; ++i) pal[i].reset();
    for (int i = 0; i < n; ++i) pal[i].set(i);
    for (int len = 2; len <= n; ++len) {
        for (int l = 0; l + len - 1 < n; ++l) {
            int r = l + len - 1;
            if (s[l] == s[r]) {
                if (len == 2) pal[l].set(r);
                else if (pal[l+1].test(r-1)) pal[l].set(r);
            }
        }
    }

    vector<short> level((size_t)n * n, 0);
    auto idx = [&](int l, int r)->size_t { return (size_t)l * n + r; };

    vector<int> cntLevel(n + 1, 0); 

    for (int len = 1; len <= n; ++len) {
        for (int l = 0; l + len - 1 < n; ++l) {
            int r = l + len - 1;
            if (!pal[l].test(r)) continue;
            int half = len / 2;
            short lev = 1;
            if (half > 0) {
                short leftLev = level[idx(l, l + half - 1)];
                lev = (short)(1 + leftLev);
            }
            level[idx(l,r)] = lev;
            if (lev <= n) cntLevel[lev] += 1;
        }
    }
    vector<long long> res(n + 1, 0);
    long long suffix = 0;
    for (int t = n; t >= 1; --t) {
        suffix += cntLevel[t];
        res[t] = suffix;
    }

    for (int k = 1; k <= n; ++k) {
        if (k > 1) cout << ' ';
        cout << res[k];
    }
    cout << '\n';
    return 0;
}
