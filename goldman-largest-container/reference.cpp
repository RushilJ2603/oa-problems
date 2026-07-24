#include <bits/stdc++.h>
using namespace std;
int main(){
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int n; if(!(cin>>n)) return 0;
    vector<int> a(n); for(auto&x:a)cin>>x;
    int m; cin>>m;
    vector<long long> fp(m),sp(m),sl(m);
    for(auto&x:fp)cin>>x; for(auto&x:sp)cin>>x; for(auto&x:sl)cin>>x;
    auto md=[&](long long v)->int{ v%=n; if(v<0)v+=n; return (int)v; };
    vector<pair<int,int>> E(m);
    for(int i=0;i<m;i++) E[i]={md(fp[i]-sl[i]), md(sp[i]+sl[i])};
    // Each swap used at most once, any order -> BFS over (array, used-mask); keep best array.
    auto ser=[&](const vector<int>&arr,int mask){ string s; for(int v:arr){ s+=to_string(v); s.push_back(','); } s.push_back('|'); s+=to_string(mask); return s; };
    vector<int> best=a;
    unordered_set<string> vis; vis.reserve(1<<16);
    queue<pair<vector<int>,int>> q; q.push({a,0}); vis.insert(ser(a,0));
    while(!q.empty()){
        auto cur=q.front().first; int mask=q.front().second; q.pop();
        if(cur>best) best=cur;
        for(int i=0;i<m;i++) if(!(mask&(1<<i))){
            vector<int> nx=cur; swap(nx[E[i].first], nx[E[i].second]); int nm=mask|(1<<i);
            if(vis.insert(ser(nx,nm)).second) q.push({nx,nm});
        }
    }
    for(int i=0;i<n;i++) cout<<best[i]<<" \n"[i+1==n];
}
