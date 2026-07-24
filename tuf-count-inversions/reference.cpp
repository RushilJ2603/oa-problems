#include <bits/stdc++.h>
using namespace std;
long long inv=0;
void ms(vector<long long>&a,int l,int r){ if(r-l<=1) return; int m=(l+r)/2; ms(a,l,m); ms(a,m,r);
  vector<long long> t; int i=l,j=m; while(i<m&&j<r){ if(a[i]<=a[j]) t.push_back(a[i++]); else { inv+=m-i; t.push_back(a[j++]); } }
  while(i<m)t.push_back(a[i++]); while(j<r)t.push_back(a[j++]); for(int k=l;k<r;k++)a[k]=t[k-l]; }
int main(){ios::sync_with_stdio(false);cin.tie(nullptr);int n;if(!(cin>>n))return 0;vector<long long>a(n);for(auto&x:a)cin>>x;ms(a,0,n);cout<<inv<<"\n";}
