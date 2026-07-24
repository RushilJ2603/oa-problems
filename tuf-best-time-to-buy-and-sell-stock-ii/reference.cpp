#include <bits/stdc++.h>
using namespace std;
int main(){ios::sync_with_stdio(false);cin.tie(nullptr);int n;if(!(cin>>n))return 0;vector<long long>a(n);for(auto&x:a)cin>>x;long long p=0;for(int i=1;i<n;i++)if(a[i]>a[i-1])p+=a[i]-a[i-1];cout<<p<<"\n";}
