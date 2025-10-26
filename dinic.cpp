#include <bits/stdc++.h>
using namespace std;
const long long INF=1e18;
int n,m,s,t;
vector<int> lvl,ptr;
vector<vector<int>> adj;
vector<int> from,to;
vector<long long> cap,flw;

void addedge(int a,int b,long long c){
    from.push_back(a);
    to.push_back(b);
    cap.push_back(c);
    flw.push_back(0);
    adj[a].push_back((int)from.size()-1);
    from.push_back(b);
    to.push_back(a);
    cap.push_back(0);
    flw.push_back(0);
    adj[b].push_back((int)from.size()-1);
}

bool bfs(){
    fill(lvl.begin(),lvl.end(),-1);
    queue<int> q;
    q.push(s);
    lvl[s]=0;
    while(!q.empty()){
        int v=q.front();q.pop();
        for(int i:adj[v]){
            if(cap[i]-flw[i]<=0) continue;
            if(lvl[to[i]]!=-1) continue;
            lvl[to[i]]=lvl[v]+1;
            q.push(to[i]);
        }
    }
    return lvl[t]!=-1;
}

long long dfs(int v,long long pushed){
    if(!pushed) return 0;
    if(v==t) return pushed;
    for(int &cid=ptr[v];cid<(int)adj[v].size();cid++){
        int i=adj[v][cid];
        if(lvl[to[i]]!=lvl[v]+1||cap[i]-flw[i]<=0) continue;
        long long tr=dfs(to[i],min(pushed,cap[i]-flw[i]));
        if(!tr) continue;
        flw[i]+=tr;
        flw[i^1]-=tr;
        return tr;
    }
    return 0;
}

long long dinic(){
    long long f=0;
    while(bfs()){
        fill(ptr.begin(),ptr.end(),0);
        while(long long pushed=dfs(s,INF)) f+=pushed;
    }
    return f;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin>>n>>m>>s>>t;
    adj.assign(n,{});
    lvl.resize(n);
    ptr.resize(n);
    for(int i=0;i<m;i++){
        int a,b;long long c;
        cin>>a>>b>>c;
        addedge(a,b,c);
    }
    cout<<dinic()<<"\n";
    return 0;
}