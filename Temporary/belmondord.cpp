#include <iostream>
#include <vector>
#include <limits>
#include <queue>

using namespace std;

// A struct to represent a weighted edge in the graph
struct Edge {
    int u, v;
    long long w;
};

int main() {
    // Fast I/O
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, s; // n: nodes, m: edges, s: source
    if (!(cin >> n >> m >> s)) {
        return 0; // Exit if input is empty
    }
    --s; // Convert 1-based source to 0-based index

    vector<Edge> edges;
    edges.reserve(m);
    
    // Adjacency list for propagating negative cycle influence
    vector<vector<int>> adj(n); 

    // Read all edges
    for (int i = 0; i < m; ++i) {
        int u, v;
        long long w;
        cin >> u >> v >> w;
        --u; --v; // Convert 1-based nodes to 0-based
        edges.push_back({u, v, w});
        adj[u].push_back(v); // Store for later
    }

    const long long INF = numeric_limits<long long>::max() / 4;
    vector<long long> dist(n, INF);
    dist[s] = 0;

    // --- Phase 1: Standard Bellman-Ford Relaxation ---
    // Relax all edges n-1 times. After this, all nodes not affected
    // by a negative cycle will have their shortest path distance.
    for (int i = 0; i < n - 1; ++i) {
        for (const auto& edge : edges) {
            if (dist[edge.u] != INF && dist[edge.v] > dist[edge.u] + edge.w) {
                dist[edge.v] = dist[edge.u] + edge.w;
            }
        }
    }

    // --- Phase 2: Detect Nodes Affected by Negative Cycles ---
    // Any node whose distance can still be improved is part of or
    // reachable from a negative cycle.
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

    // --- Phase 3: Propagate Negative Cycle Influence ---
    // Any node reachable from a node affected by a negative cycle also
    // has a shortest path of negative infinity. We use a BFS for this.
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

    // --- Phase 4: Print the Results ---
    for (int i = 0; i < n; ++i) {
        if (i > 0) {
            cout << " ";
        }
        if (dist[i] >= INF / 2) {
            cout << "INF"; // Unreachable
        } else if (affected_by_neg_cycle[i]) {
            cout << "-INF"; // Affected by a negative cycle
        } else {
            cout << dist[i]; // Finite shortest path
        }
    }
    cout << '\n';

    return 0;
}