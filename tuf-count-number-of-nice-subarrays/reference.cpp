#include <bits/stdc++.h>
using namespace std;
long long atMost(vector<int>&o,int k){ if(k<0) return 0; long long res=0; int l=0,s=0; for(int r=0;r<(int)o.size();r++){ s+=o[r]; while(s>k) s-=o[l++]; res+=r-l+1; } return res; }
int main(){ios::sync_with_stdio(false);cin.tie(nullptr);int n,k;if(!(cin>>n>>k))return 0;vector<int>o(n);for(int i=0;i<n;i++){int v;cin>>v;o[i]=v&1;}cout<<atMost(o,k)-atMost(o,k-1)<<"\n";}
