#include <bits/stdc++.h>
using namespace std;
long long INF = 1e15;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);

    int m, p;
    long long l;
    while(cin >> m >> p >> ){
        vector<tuple<int,int,long long>> v;
        vector<vector<long long>> mat(m+1, vector<long long>(m+1, INF));
        for(int i=1;i<=m;i++) mat[i][i]=0;
        for(int i=0;i<p;i++){
            int a,b; long long c;
            cin >> a >> b >> c;
            v.push_back({a,b,c});
            mat[a][b]=min(mat[a][b],c);
            mat[b][a]=min(mat[b][a],c);
        }
        for(int k=1;k<=m;k++)
            for(int i=1;i<=m;i++)
                for(int j=1;j<=m;j++)
                    if(mat[i][k]+mat[k][j]<mat[i][j]) mat[i][j]=mat[i][k]+mat[k][j];

        auto vk=[&](vector<vector<long long>> &d){
            long long zbir=0;
            for(int i=1;i<=m;i++){
                for(int j=1;j<=m;j++){
                    if(d[i][j]>=INF/2) zbir+=l;
                    else zbir+=d[i][j];
                }
            }
            return zbir;
        };

        long long s=vk(mat);
        long long maxx=s;

        for(auto [a,b,c]:v){
            vector<vector<long long>> d(m+1, vector<long long>(m+1,INF));
            for(int i=1;i<=m;i++) d[i][i]=0;
            bool skok=false;
            for(auto [x,y,z]:v){
                if(!skok && ((x==a && y==b && z==c)||(x==b && y==a && z==c))){
                    skok=true;
                    continue;
                }
                d[x][y]=min(d[x][y],z);
                d[y][x]=min(d[y][x],z);
            }
            for(int k=1;k<=m;k++)
                for(int i=1;i<=m;i++)
                    for(int j=1;j<=m;j++)
                        if(d[i][k]+d[k][j]<d[i][j]) d[i][j]=d[i][k]+d[k][j];
            long long s=vk(d);
            if(s>maxx) maxx=s;
        }
        cout << s << " " << maxx << "\n";
    }
}