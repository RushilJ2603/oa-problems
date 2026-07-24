#include <bits/stdc++.h>
using namespace std;
int main(){ios::sync_with_stdio(false);cin.tie(nullptr);int n;long long k;if(!(cin>>n>>k))return 0;
    vector<long long> a(n); for(auto&x:a)cin>>x;
    sort(a.begin(),a.end());
    int i=0; while(k>0 && i<n && a[i]<0){ a[i]=-a[i]; k--; i++; }
    long long sum=0, mn=LLONG_MAX;
    for(auto x:a){ sum+=x; mn=min(mn, llabs(x)); }
    if(k>0 && (k%2==1)) sum-=2*mn;
    cout<<sum<<"\n";
}
