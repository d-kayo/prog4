#include <bits/stdc++.h>
using namespace std;


int bfs(int n,int s,int t,vector<vector<int>>&graph,vector<vector<int>>&cap,vector<int> &parent)
{
    parent.clear();
    for(int i=0;i<n;i++)
    {
        parent.push_back(-1);
    }

    parent[s]=-2;

    queue<pair<int,int>> q;
    q.push({s,INT_MAX});

    while(!q.empty())
    {
        auto h=q.front();
        q.pop();

        int node=h.first;
        int flow=h.second;

        for(auto next:graph[node])
        {
            if(parent[next]==-1 && cap[node][next])
            {
                parent[next] = node;
                int newf = min(flow,cap[node][next]);

                if(next==t)
                return newf;

                q.push({next,newf});
            }
        }


    }

    return 0;
}


int ford(int n, int s, int t, vector<vector<int>> & graph, vector<vector<int>> &cap)
{
    int flow=0;
    int newf=0;
    vector<int> parent;
    while(newf = bfs(n,s,t,graph,cap,parent))
    {
        int now = t;
        flow += newf;
        while(now!=s)
        {
           
            int before = parent[now];
            cap[before][now] -= newf;
            cap[now][before] += newf;
            now = before;
        }
    }

    return flow;
}



int main()
{
    int n=0, m=0, s=0, t=0;
    cin >> n >> m >> s >> t;
    int x = INT_MAX;

    vector<vector<int>> edg;
    vector<vector<int>> graph(n,vector<int>());
    vector<vector<int>> cap(n,vector<int>(n,0)), d;


    int maxe = 0;

    for(int i=0;i<m;i++)
    {
        int a=0,b=0,w=0;
        cin >> a >> b >> w;

        cap[a][b] = w;
        graph[a].push_back(b);
        graph[b].push_back(a);
        edg.push_back({a,b,w});
    }

    pair<int,int>rmv={0,0};

    for(auto e:edg)
    {
        d = cap;
        int a = e[0];
        int b = e[1];
        int temp = d[a][b];

        d[a][b] = 0;

        auto it = find(graph[a].begin(), graph[a].end(), b);
        if (it != graph[a].end())
        {
            graph[a].erase(it);
        }

        it = find(graph[b].begin(), graph[b].end(), a);
        if (it != graph[b].end())
        {
            graph[b].erase(it);
        }

        int rez=ford(n,s,t,graph,d);
        if (rez<x)
        {
            rmv.first=e[0];
            rmv.second=e[1];
            x=rez;
        }
       
        graph[a].push_back(b);
        graph[b].push_back(a);
        d[a][b]=temp;
    }
   
    cout<<x<<endl;
    cout<<rmv.first<<' '<<rmv.second;

    return 0;
}