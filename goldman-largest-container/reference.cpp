#include <bits/stdc++.h>
using namespace std;
int main(){ios::sync_with_stdio(false);cin.tie(nullptr);int n;if(!(cin>>n))return 0;
  vector<long long> a(n); for(auto&x:a)cin>>x;
  int m; cin>>m;
  vector<long long> fp(m),sp(m),sl(m);
  for(auto&x:fp)cin>>x; for(auto&x:sp)cin>>x; for(auto&x:sl)cin>>x;
  vector<int> p(n); iota(p.begin(),p.end(),0);
  function<int(int)> f=[&](int x){ while(p[x]!=x){ p[x]=p[p[x]]; x=p[x]; } return x; };
  auto md=[&](long long v)->int{ v%=n; if(v<0)v+=n; return (int)v; };
  for(int i=0;i<m;i++){ int i1=md(fp[i]-sl[i]); int i2=md(sp[i]+sl[i]); p[f(i1)]=f(i2); }
  unordered_map<int, vector<int>> comp;
  for(int i=0;i<n;i++) comp[f(i)].push_back(i);   // positions ascending
  vector<long long> res(n);
  for(auto& kv:comp){ vector<long long> vals; for(int idx:kv.second) vals.push_back(a[idx]);
    sort(vals.rbegin(), vals.rend());
    for(size_t j=0;j<kv.second.size();j++) res[kv.second[j]]=vals[j]; }
  for(int i=0;i<n;i++) cout<<res[i]<<" \n"[i+1==n];
}
