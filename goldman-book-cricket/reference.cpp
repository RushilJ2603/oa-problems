#include <bits/stdc++.h>
using namespace std;
int main(){
    long long n; if(!(cin>>n)) return 0;
    if(n<0){cout<<0<<"\n";return 0;}
    vector<unsigned long long> dp(n+1,0); dp[0]=1;
    for(long long i=1;i<=n;i++){
        if(i>=2) dp[i]+=dp[i-2];
        if(i>=4) dp[i]+=dp[i-4];
        if(i>=6) dp[i]+=dp[i-6];
    }
    cout<<dp[n]<<"\n";
    return 0;
}
