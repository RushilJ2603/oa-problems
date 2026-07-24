#include <bits/stdc++.h>
using namespace std;
int main(){ios::sync_with_stdio(false);cin.tie(nullptr);int n;if(!(cin>>n))return 0;vector<long long>r(n);for(auto&x:r)cin>>x;
  vector<long long>c(n,1);for(int i=1;i<n;i++)if(r[i]>r[i-1])c[i]=c[i-1]+1;for(int i=n-2;i>=0;i--)if(r[i]>r[i+1])c[i]=max(c[i],c[i+1]+1);
  long long s=0;for(auto v:c)s+=v;cout<<s<<"\n";}
