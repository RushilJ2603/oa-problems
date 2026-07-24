#include <bits/stdc++.h>
using namespace std;
int main(){ios::sync_with_stdio(false);cin.tie(nullptr);int n;if(!(cin>>n))return 0;
    vector<long long> a(n); for(auto&x:a)cin>>x;
    vector<char> comp(n+1,0); if(n>=0)comp[0]=1; if(n>=1)comp[1]=1;
    for(int p=2;(long long)p*p<=n;p++) if(!comp[p]) for(int q=p*p;q<=n;q+=p) comp[q]=1;
    vector<int> primes3; for(int p=3;p<n;p++) if(!comp[p] && p%10==3) primes3.push_back(p);
    const long long NEG=LLONG_MIN/4;
    vector<long long> dp(n,NEG); dp[0]=a[0];
    for(int i=1;i<n;i++){
        long long best=dp[i-1];
        for(int p:primes3){ if(p>i)break; best=max(best,dp[i-p]); }
        dp[i]=a[i]+best;
    }
    cout<<dp[n-1]<<"\n";
}
