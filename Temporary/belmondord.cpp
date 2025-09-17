#include <iostream>
#include <vector>
#include <limits>
#include <queue>

using namespace std;


struct Edge {
    int u, v;
    long long w;
};

int main() {
    

    int n, m, s; 
    if (!(cin >> n >> m >> s)) {
        return 0; 
    }
    --s; 

    vector<Edge> edges;
    edges.reserve(m);
    
    
    vector<vector<int>> adj(n); 

    for (int i = 0; i < m; ++i) {
        int u, v;
        long long w;
        cin >> u >> v >> w;
        --u; --v; 
        edges.push_back({u, v, w});
        adj[u].push_back(v); 
    }

    const long long INF = numeric_limits<long long>::max() / 4;
    vector<long long> dist(n, INF);
    dist[s] = 0;

   
    for (int i = 0; i < n - 1; ++i) {
        for (const auto& edge : edges) {
            if (dist[edge.u] != INF && dist[edge.v] > dist[edge.u] + edge.w) {
                dist[edge.v] = dist[edge.u] + edge.w;
            }
        }
    }

    vector<bool> affected_by_neg_cycle(n, false);
    queue<int> q;

    for (const auto& edge : edges) {
        if (dist[edge.u] != INF && dist[edge.v] > dist[edge.u] + edge.w) {
            if (!affected_by_neg_cycle[edge.v]) {
                affected_by_neg_cycle[edge.v] = true;
                q.push(edge.v);
            }
        }
    }

   
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int v : adj[u]) {
            if (!affected_by_neg_cycle[v]) {
                affected_by_neg_cycle[v] = true;
                q.push(v);
            }
        }
    }

    for (int i = 0; i < n; ++i) {
        if (i > 0) {
            cout << " ";
        }
        if (dist[i] >= INF / 2) {
            cout << "INF"; 
        } else if (affected_by_neg_cycle[i]) {
            cout << "-INF";
        } else {
            cout << dist[i]; 
        }
    }
    cout << '\n';

    return 0;
}