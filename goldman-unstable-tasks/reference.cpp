#include <bits/stdc++.h>
using namespace std;
int main(){ios::sync_with_stdio(false);cin.tie(nullptr);int n;if(!(cin>>n))return 0;
  vector<string> t(n); for(auto&s:t)cin>>s;
  vector<long long> ts(n),lim(n); for(auto&x:ts)cin>>x; for(auto&x:lim)cin>>x;
  unordered_map<string, vector<pair<long long,long long>>> M;
  for(int i=0;i<n;i++) M[t[i]].push_back({ts[i], lim[i]});
  int cnt=0;
  for(auto& kv:M){ auto v=kv.second; sort(v.begin(),v.end());
    bool inc=false,dec=false;
    for(size_t i=1;i<v.size();i++){ if(v[i].second>v[i-1].second)inc=true; else if(v[i].second<v[i-1].second)dec=true; }
    if(inc&&dec)cnt++; }
  cout<<cnt<<"\n";
}
