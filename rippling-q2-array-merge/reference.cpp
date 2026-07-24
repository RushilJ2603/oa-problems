// Two arrays of POSITIVE integers. One op = replace any contiguous subarray with its sum (merging
// a block of length L>=2 costs 1 op; length-1 is a no-op). Min ops to make X and Y identical.
// The op preserves each array's total, so if sums differ it's impossible (-1).
// A target Z corresponds to a set of "cut" prefix sums common to X and Y. Between consecutive kept
// cuts, X spends 1 op iff it spans >=2 elements, likewise Y. Choosing WHICH common cuts to keep is a
// DP (keeping all is NOT always optimal): dp[k] = min_{t<k} dp[t] + [Xspan>=2] + [Yspan>=2].
#include <bits/stdc++.h>
using namespace std;
int main(){
    int n; if(!(cin>>n)) return 0;
    vector<long long> X(n); for(auto&x:X)cin>>x;
    int m; cin>>m;
    vector<long long> Y(m); for(auto&y:Y)cin>>y;
    vector<long long> PX(n+1,0), PY(m+1,0);
    for(int i=0;i<n;i++) PX[i+1]=PX[i]+X[i];
    for(int j=0;j<m;j++) PY[j+1]=PY[j]+Y[j];
    if(PX[n]!=PY[m]){ cout<<-1<<"\n"; return 0; }
    // common prefix sums (both strictly increasing since values positive)
    vector<pair<int,int>> cuts;              // (index in PX, index in PY)
    int i=0,j=0;
    while(i<=n && j<=m){
        if(PX[i]==PY[j]){ cuts.push_back({i,j}); i++; j++; }
        else if(PX[i]<PY[j]) i++;
        else j++;
    }
    int c=cuts.size();
    vector<int> dp(c, INT_MAX);
    dp[0]=0;
    for(int k=1;k<c;k++)
        for(int t=0;t<k;t++){
            if(dp[t]==INT_MAX) continue;
            int cost = (cuts[k].first-cuts[t].first>=2?1:0) + (cuts[k].second-cuts[t].second>=2?1:0);
            dp[k]=min(dp[k], dp[t]+cost);
        }
    cout<<dp[c-1]<<"\n";
    return 0;
}
