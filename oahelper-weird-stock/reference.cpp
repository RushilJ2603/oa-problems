#include <bits/stdc++.h>
using namespace std;
int main(){ios::sync_with_stdio(false);cin.tie(nullptr);int n,m;if(!(cin>>n>>m))return 0;
    if(m<=n){ cout<<n-m<<"\n"; return 0; }
    int CAP=2*max(n,m)+2;
    vector<int> dist(CAP+1,-1); queue<int>q; dist[n]=0; q.push(n);
    while(!q.empty()){ int x=q.front();q.pop(); if(x==m)break;
        int a=x-1, b=2*x;
        if(a>=1 && dist[a]==-1){ dist[a]=dist[x]+1; q.push(a); }
        if(b<=CAP && dist[b]==-1){ dist[b]=dist[x]+1; q.push(b); } }
    cout<<dist[m]<<"\n";
}
