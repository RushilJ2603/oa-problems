// Dora: longest simple path S->D in an undirected graph (adjacency matrix). Among the longest,
// output the lexicographically smallest vertex sequence. Backtracking DFS, neighbours in
// increasing order; keep the best (more cities, then lex-smaller).
#include <bits/stdc++.h>
using namespace std;
int n, S, D;
vector<vector<int>> g;
vector<int> path, best;
vector<char> vis;
bool better(const vector<int>&a,const vector<int>&b){ // is a better than b?
    if(b.empty()) return true;
    if(a.size()!=b.size()) return a.size()>b.size();
    return a<b; // lex smaller
}
void dfs(int u){
    if(u==D){ if(better(path,best)) best=path; return; }
    for(int v=0;v<n;v++) if(g[u][v] && !vis[v]){
        vis[v]=1; path.push_back(v); dfs(v); path.pop_back(); vis[v]=0;
    }
}
int main(){
    if(!(cin>>n)) return 0;
    g.assign(n,vector<int>(n));
    for(auto&r:g) for(auto&x:r) cin>>x;
    cin>>S>>D;
    vis.assign(n,0); vis[S]=1; path.push_back(S);
    if(S==D){ best=path; }
    else dfs(S);
    for(size_t i=0;i<best.size();i++) cout<<best[i]<<" \n"[i+1==best.size()];
    if(best.empty()) cout<<"\n";
    return 0;
}
