#include <bits/stdc++.h>
using namespace std;

using ll = long long;
const ll INF = 4e18;

int main() {
    

    int n, m;
    cin >> n >> m;

    vector<vector<pair<int,ll>>> adj(n);
    for (int i = 0; i < m; i++) {
        int u, v;
        ll w;
        cin >> u >> v >> w;
        
        adj[u].push_back({v, w});
       
    }

    int s;
    cin >> s; 
    

    vector<ll> dist(n, INF);
    dist[s] = 0;
    priority_queue<pair<ll,int>, vector<pair<ll,int>>, greater<>> pq;
    pq.push({0, s});

    while (!pq.empty()) {
        auto [d, u] = pq.top(); pq.pop();
        if (d != dist[u]) continue;
        for (auto [v, w] : adj[u]) {
            if (dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                pq.push({dist[v], v});
            }
        }
    }

    for (int i = 0; i < n; i++) {
        if (dist[i] == INF) cout << "INF\n";
        else cout << dist[i] << "\n";
    }
}
