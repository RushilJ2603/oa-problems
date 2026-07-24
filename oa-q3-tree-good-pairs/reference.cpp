// Tree good pairs. Rooted at 0. For each strict ancestor u of v, path weight = ds[v]-ds[u]
// (ds = sum of edge weights from root). Good pair: ds[v]-ds[u] <= nodeW[v]  <=>  ds[u] >= ds[v]-nodeW[v].
// Edge weights are non-negative, so ds is non-decreasing along a root path -> binary search the
// ancestor stack. Iterative DFS to survive deep (path) trees.
#include <bits/stdc++.h>
using namespace std;
int main(){
    int n; if(!(cin>>n)) return 0;
    vector<long long> w(n);
    for(auto&x:w) cin>>x;
    vector<vector<pair<int,long long>>> adj(n);
    for(int i=0;i<n-1;i++){int a,b; long long c; cin>>a>>b>>c; adj[a].push_back({b,c}); adj[b].push_back({a,c});}
    vector<long long> ds(n,0);
    vector<long long> pathDS;                 // ds of strict ancestors on current root-path (non-decreasing)
    long long ans=0;
    // iterative DFS with ENTER/LEAVE phases
    // frame: (node, parent, phase) phase 0=enter,1=leave
    vector<array<long long,3>> st;
    st.push_back({0,-1,0});
    while(!st.empty()){
        auto fr=st.back(); st.pop_back();
        int v=fr[0], p=(int)fr[1]; long long phase=fr[2];
        if(phase==0){
            // ds[v] set when we compute here (parent already entered)
            long long threshold = ds[v]-w[v];
            // count strict ancestors with ds >= threshold
            ans += (long long)(pathDS.end() - lower_bound(pathDS.begin(), pathDS.end(), threshold));
            pathDS.push_back(ds[v]);
            st.push_back({(long long)v,(long long)p,1});
            for(auto&e:adj[v]) if(e.first!=p){ ds[e.first]=ds[v]+e.second; st.push_back({(long long)e.first,(long long)v,0}); }
        } else {
            pathDS.pop_back();
        }
    }
    cout<<ans<<"\n";
    return 0;
}
