#include <bits/stdc++.h>
using namespace std;
int main(){ios::sync_with_stdio(false);cin.tie(nullptr);int n;long long k;if(!(cin>>n>>k))return 0;
  unordered_map<long long,long long>cnt;cnt.reserve(n*2);cnt[0]=1;long long x=0,ans=0;
  for(int i=0;i<n;i++){long long v;cin>>v;x^=v;auto it=cnt.find(x^k);if(it!=cnt.end())ans+=it->second;cnt[x]++;}cout<<ans<<"\n";}
