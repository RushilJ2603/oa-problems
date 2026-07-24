#include <bits/stdc++.h>
using namespace std;
int main(){ios::sync_with_stdio(false);cin.tie(nullptr);int n,m;if(!(cin>>n>>m))return 0;vector<long long>a(n);for(auto&x:a)cin>>x;
  if(m>n){cout<<-1<<"\n";return 0;} long long lo=*max_element(a.begin(),a.end()),hi=accumulate(a.begin(),a.end(),0LL),ans=hi;
  auto ok=[&](long long cap){long long s=0;int c=1;for(int i=0;i<n;i++){if(s+a[i]>cap){c++;s=a[i];}else s+=a[i];}return c<=m;};
  while(lo<=hi){long long mid=(lo+hi)/2; if(ok(mid)){ans=mid;hi=mid-1;} else lo=mid+1;} cout<<ans<<"\n";}
