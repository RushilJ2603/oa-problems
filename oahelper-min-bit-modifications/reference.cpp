#include <bits/stdc++.h>
using namespace std;
int main(){ios::sync_with_stdio(false);cin.tie(nullptr);int n;if(!(cin>>n))return 0;
    vector<unsigned long long> a(n); for(auto&x:a)cin>>x;
    long long ans=0;
    for(int b=0;b<63;b++){ long long ones=0; for(auto x:a) if((x>>b)&1ULL)ones++; ans+=min(ones,(long long)n-ones); }
    cout<<ans<<"\n";
}
