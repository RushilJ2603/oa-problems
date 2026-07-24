#include <bits/stdc++.h>
using namespace std;
int main(){ios::sync_with_stdio(false);cin.tie(nullptr);int n;if(!(cin>>n))return 0;
    vector<long long> A(n); for(auto&x:A)cin>>x;
    unordered_map<long long,vector<int>> g; g.reserve(n*2);
    for(int i=0;i<n;i++) g[A[i]].push_back(i);
    vector<char> keep(n,0); vector<long long> val(n,0);
    for(auto&kv:g){ auto&idx=kv.second; long long s=kv.first*(long long)idx.size();
        int mid=idx[idx.size()/2]; keep[mid]=1; val[mid]=s; }
    bool first=true;
    for(int i=0;i<n;i++) if(keep[i]){ if(!first)cout<<' '; cout<<val[i]; first=false; }
    cout<<"\n";
}
