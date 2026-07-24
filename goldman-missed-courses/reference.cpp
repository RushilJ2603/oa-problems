#include <bits/stdc++.h>
using namespace std;
int main(){ios::sync_with_stdio(false);cin.tie(nullptr);long long nc,fd,ld;if(!(cin>>nc>>fd>>ld))return 0;
  long long len=ld-fd+1;                 // number of missed days
  cout<<min(len,nc)<<"\n";              // consecutive integers mod nc -> min(len, nc) distinct residues
}
