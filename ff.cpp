#include <bits/stdc++.h>
using namespace std;

bool dfs(int u,int t,vector<vector<int>>&cap,vector<vector<int>>&adj,vector<int> &parent,vector<bool>&vis) {
    vis[u]=true;
    if (u==t)return true;
    for (int v:adj[u]) {
        if (!vis[v]&&cap[u][v]>0) {
            parent[v]=u;
            if (dfs(v,t,cap,adj,parent,vis))return true;
        }
    }
    return false;
}

int ford(int n,vector<vector<int>>&cap,vector<vector<int>>&adj,int s,int t) {
    int maxflow= 0;
    vector<int>parent(n);

    while (true){
        vector<bool>vis(n,false);
        fill(parent.begin(),parent.end(),-1);
        if (!dfs(s,t,cap,adj,parent,vis))break;

        int path=INT_MAX;
        for (int v=t;v!=s;v=parent[v])
            path=min(path,cap[parent[v]][v]);

        vector<int> pathflow; 
        for (int v=t;v!= -1;v=parent[v])
            pathflow.push_back(v);
        reverse(pathflow.begin(),pathflow.end());

        for (int i=0;i<(int)pathflow.size();i++)
            cout<<pathflow[i]<<(i+1<(int)pathflow.size()?' ':'\n');

        for (int v=t;v!=s;v=parent[v]) {
            int u=parent[v];
            cap[u][v]-=path;
            cap[v][u]+=path;
        }

        maxflow+=path;
    }

    cout<<maxflow<<"\n";
    return maxflow;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n,m;
    cin>>n>>m;
    vector<vector<int>>cap(n,vector<int>(n,0));
    vector<vector<int>>adj(n);

    for (int i=0;i<m;i++) {
        int u,v,c;
        cin>>u>>v>>c;
        cap[u][v]+=c;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    int s,t;
    cin>>s>>t;

    ford(n,cap,adj,s,t);
}