#include <bits/stdc++.h>
using namespace std;

struct Edge {
    int u, v;
    double w;
};

void floydWarshall(int n, const vector<Edge>& edges) {
    const double INF = 1e18;
    vector<vector<double>> dist(n, vector<double>(n, INF));
    vector<vector<int>> next(n, vector<int>(n, -1));

    for (int i = 0; i < n; i++) {
        dist[i][i] = 0;
        next[i][i] = i;
    }
    for (const auto &e : edges) {
        if (e.w < dist[e.u][e.v]) { 
            dist[e.u][e.v] = e.w;
            next[e.u][e.v] = e.v;
        }
    }


    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            if (dist[i][k] == INF) continue;
            for (int j = 0; j < n; j++) {
                if (dist[k][j] == INF) continue;
                double newDist = dist[i][k] + dist[k][j];
                if (newDist < dist[i][j]) {
                    dist[i][j] = newDist;
                    next[i][j] = next[i][k];
                }
            }
        }
    }

    
    bool hasNegCycle = false;
    for (int i = 0; i < n; i++) {
        if (dist[i][i] < 0) hasNegCycle = true;
    }

    cout << "Negative cycle present? " << (hasNegCycle ? "YES" : "NO") << "\n";

    cout << "Distance matrix:\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (dist[i][j] == INF) cout << "INF ";
            else cout << dist[i][j] << " ";
        }
        cout << "\n";
    }
}

int main() {
    vector<Edge> edges = {
        {0, 1, 3},
        {0, 2, 8},
        {0, 4, -4},
        {1, 3, 1},
        {1, 4, 7},
        {2, 1, 4},
        {3, 0, 2},
        {4, 3, 6}
    };

    int n = 5; 
    floydWarshall(n, edges);

    return 0;
}
