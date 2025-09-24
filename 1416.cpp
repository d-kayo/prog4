#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const ll INF = (1LL << 60);

struct Edge { int u, v, w; };
struct AdjEdge { int to, w, idx; };

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    ll L;
    cin >> n >> m >> L;   // read exactly one test case

    vector<Edge> edges(m);
    vector<vector<AdjEdge>> adj(n + 1);

    for (int i = 0; i < m; ++i) {
        int a, b, s;
        cin >> a >> b >> s;
        edges[i] = {a, b, s};
        adj[a].push_back({b, s, i});
        adj[b].push_back({a, s, i});
    }

    auto dijkstra = [&](int src, int removed_idx) {
        vector<ll> dist(n + 1, INF);
        dist[src] = 0;
        priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<>> pq;
        pq.push({0, src});
        while (!pq.empty()) {
            auto [d, u] = pq.top(); pq.pop();
            if (d != dist[u]) continue;
            for (auto &e : adj[u]) {
                if (e.idx == removed_idx) continue;
                int v = e.to;
                ll nd = d + e.w;
                if (nd < dist[v]) {
                    dist[v] = nd;
                    pq.push({nd, v});
                }
            }
        }
        return dist;
    };

    // 1) Compute all-pairs shortest paths for original graph
    vector<vector<ll>> dist0(n + 1, vector<ll>(n + 1, INF));
    vector<ll> sum_from(n + 1, 0);
    ll total_orig = 0;

    for (int s = 1; s <= n; ++s) {
        auto d = dijkstra(s, -1);
        for (int t = 1; t <= n; ++t) {
            dist0[s][t] = d[t];
            sum_from[s] += (d[t] == INF ? L : d[t]);
        }
        total_orig += sum_from[s];
    }

    ll best_after = total_orig;

    // 2) Try removing each edge
    for (int ei = 0; ei < m; ++ei) {
        int u = edges[ei].u, v = edges[ei].v, w = edges[ei].w;

        vector<char> affected(n + 1, 0);

        // Detect affected sources: if any (s,t) shortest path uses this edge
        for (int s = 1; s <= n; ++s) {
            for (int t = 1; t <= n; ++t) {
                ll d = dist0[s][t];
                if (d == INF) continue;
                bool uses_edge =
                    (dist0[s][u] != INF && dist0[v][t] != INF &&
                     d == dist0[s][u] + w + dist0[v][t]) ||
                    (dist0[s][v] != INF && dist0[u][t] != INF &&
                     d == dist0[s][v] + w + dist0[u][t]);
                if (uses_edge) {
                    affected[s] = 1;
                    break; // only need to mark s once
                }
            }
        }

        ll tot_after = 0;
        for (int s = 1; s <= n; ++s) {
            if (!affected[s]) {
                tot_after += sum_from[s]; // unchanged
            } else {
                auto d = dijkstra(s, ei);
                for (int t = 1; t <= n; ++t)
                    tot_after += (d[t] == INF ? L : d[t]);
            }
        }
        best_after = max(best_after, tot_after);
    }

    cout << total_orig << " " << best_after << "\n";
    return 0;
}
