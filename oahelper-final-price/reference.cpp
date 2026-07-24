#include <bits/stdc++.h>
using namespace std;
int main(){ios::sync_with_stdio(false);cin.tie(nullptr);int n;if(!(cin>>n))return 0;
  vector<long long>p(n);for(auto&x:p)cin>>x;
  vector<int>nxt(n,-1); stack<int>st;
  for(int i=n-1;i>=0;i--){ while(!st.empty()&&p[st.top()]>p[i]) st.pop(); if(!st.empty())nxt[i]=st.top(); st.push(i); }
  long long sum=0; vector<int>nod;
  for(int i=0;i<n;i++){ if(nxt[i]==-1){ sum+=p[i]; nod.push_back(i);} else sum+=p[i]-p[nxt[i]]; }
  cout<<sum<<"\n";
  for(size_t i=0;i<nod.size();i++) cout<<nod[i]<<" \n"[i+1==nod.size()];
  if(nod.empty()) cout<<"\n";
  return 0;}
