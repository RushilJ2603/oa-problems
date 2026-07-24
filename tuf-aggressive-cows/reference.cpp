#include <bits/stdc++.h>
using namespace std;
int main(){ios::sync_with_stdio(false);cin.tie(nullptr);int n,k;if(!(cin>>n>>k))return 0;vector<long long>a(n);for(auto&x:a)cin>>x;sort(a.begin(),a.end());
  long long lo=0,hi=a[n-1]-a[0],ans=0; auto ok=[&](long long d){long long last=a[0];int c=1;for(int i=1;i<n;i++)if(a[i]-last>=d){c++;last=a[i];}return c>=k;};
  while(lo<=hi){long long m=(lo+hi)/2; if(ok(m)){ans=m;lo=m+1;} else hi=m-1;} cout<<ans<<"\n";}
