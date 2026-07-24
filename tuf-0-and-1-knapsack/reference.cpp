#include <bits/stdc++.h>
using namespace std;
int main(){ios::sync_with_stdio(false);cin.tie(nullptr);int N,W;if(!(cin>>N>>W))return 0;vector<long long>val(N),wt(N);for(auto&x:val)cin>>x;for(auto&x:wt)cin>>x;
  vector<long long>dp(W+1,0);for(int i=0;i<N;i++)for(int w=W;w>=wt[i];w--)dp[w]=max(dp[w],dp[w-wt[i]]+val[i]);cout<<dp[W]<<"\n";}
