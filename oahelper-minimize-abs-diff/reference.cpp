#include <bits/stdc++.h>
using namespace std;
int main(){ios::sync_with_stdio(false);cin.tie(nullptr);int n,k;if(!(cin>>n>>k))return 0;
    vector<long long> a(n); for(auto&x:a)cin>>x;
    vector<long long> pre(n,0), suf(n,0);
    for(int i=1;i<n;i++) pre[i]=pre[i-1]+llabs(a[i]-a[i-1]);   // adj-diff sum within a[0..i]
    for(int i=n-2;i>=0;i--) suf[i]=suf[i+1]+llabs(a[i+1]-a[i]);// adj-diff sum within a[i..n-1]
    long long best=LLONG_MAX;
    for(int i=0;i+k<=n;i++){                                    // remove a[i..i+k-1]
        long long left  = (i>=1)? pre[i-1] : 0;
        long long right = (i+k<=n-1)? suf[i+k] : 0;
        long long junc  = (i>=1 && i+k<=n-1)? llabs(a[i-1]-a[i+k]) : 0;
        best=min(best, left+right+junc);
    }
    cout<<best<<"\n";
}
