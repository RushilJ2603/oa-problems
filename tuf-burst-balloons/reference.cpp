#include <bits/stdc++.h>
using namespace std;
int main(){ios::sync_with_stdio(false);cin.tie(nullptr);int n;if(!(cin>>n))return 0;vector<long long>a(n+2);a[0]=a[n+1]=1;for(int i=1;i<=n;i++)cin>>a[i];
  vector<vector<long long>>dp(n+2,vector<long long>(n+2,0));
  for(int len=1;len<=n;len++)for(int l=1;l+len-1<=n;l++){int r=l+len-1;long long best=0;for(int k=l;k<=r;k++){long long cur=a[l-1]*a[k]*a[r+1]+dp[l][k-1]+dp[k+1][r];best=max(best,cur);}dp[l][r]=best;}
  cout<<dp[1][n]<<"\n";}
