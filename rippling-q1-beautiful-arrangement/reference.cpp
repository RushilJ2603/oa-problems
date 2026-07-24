// Beautiful Arrangement — count permutations p of 1..n with p[i]%i==0 or i%p[i]==0 (1-based).
// Bitmask DP: dp[mask] = #ways to fill first popcount(mask) positions using the chosen set.
#include <bits/stdc++.h>
using namespace std;
int main(){
    int n; if(!(cin>>n)) return 0;
    vector<long long> dp(1<<n, 0);
    dp[0]=1;
    for(int mask=0; mask<(1<<n); ++mask){
        if(!dp[mask]) continue;
        int pos = __builtin_popcount(mask)+1;      // 1-based position to fill next
        for(int x=1; x<=n; ++x){
            if(mask&(1<<(x-1))) continue;
            if(x%pos==0 || pos%x==0) dp[mask|(1<<(x-1))] += dp[mask];
        }
    }
    cout << dp[(1<<n)-1] << "\n";
    return 0;
}
