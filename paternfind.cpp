#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const ll base = 257;
const ll mod = 1000000007;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;

    while (T--) {
        string A, B;
        cin >> A >> B;

        int n = A.size();
        int m = B.size();

        if (m > n) {
            cout << "Not Found\n\n";
            continue;
        }
        vector<ll> power(max(n, m) + 1, 1);
        for (int i = 1; i < (int)power.size(); i++) {
            power[i] = (power[i - 1] * base) % mod;
        }

        ll hashB = 0;
        for (int i = 0; i < m; i++) {
            hashB = (hashB * base + B[i]) % mod;
        }

        vector<ll> hashA(n + 1, 0);
        for (int i = 0; i < n; i++) {
            hashA[i + 1] = (hashA[i] * base + A[i]) % mod;
        }

        vector<int> matches;

        for (int i = 0; i + m <= n; i++) {
            ll currentHash = (hashA[i + m] - (hashA[i] * power[m]) % mod + mod) % mod;
            if (currentHash == hashB) { 
                matches.push_back(i + 1); 
            }
        }

        if (matches.empty()) {
            cout << "Not Found\n";
        } else {
            cout << matches.size() << "\n";
            for (int i = 0; i < matches.size(); i++) {
                cout << matches[i] << (i + 1 < matches.size() ? ' ' : '\n');
            }
        }

        if (T) cout << "\n"; 
    }

    return 0;
}
