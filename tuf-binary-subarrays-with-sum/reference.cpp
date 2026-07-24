#include <bits/stdc++.h>
using namespace std;
long long atMost(vector<int>&a,int g){ if(g<0) return 0; long long res=0; int l=0,s=0; for(int r=0;r<(int)a.size();r++){ s+=a[r]; while(s>g) s-=a[l++]; res+=r-l+1; } return res; }
int main(){ios::sync_with_stdio(false);cin.tie(nullptr);int n,g;if(!(cin>>n>>g))return 0;vector<int>a(n);for(auto&x:a)cin>>x;cout<<atMost(a,g)-atMost(a,g-1)<<"\n";}
