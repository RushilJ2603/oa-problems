#include <bits/stdc++.h>
using namespace std;
int main(){ios::sync_with_stdio(false);cin.tie(nullptr);int n;if(!(cin>>n))return 0;
  vector<long long>p(n);for(auto&x:p)cin>>x;
  long long total=p[0],mn=p[0];
  for(int i=1;i<n;i++){ total += max(0LL, p[i]-mn); mn=min(mn,p[i]); }
  cout<<total<<"\n";}
