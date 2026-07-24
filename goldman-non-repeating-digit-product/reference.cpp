#include <bits/stdc++.h>
using namespace std;
int digs(long long v){int m=0; if(v==0) return 1; while(v){m|=1<<(v%10); v/=10;} return m;}
int main(){
    long long x,y,z; if(!(cin>>x>>y>>z)) return 0;
    long long cnt=0;
    for(long long n=y;n<=z;n++){
        int dn=digs(n), dp=digs(n*x);
        if((dn&dp)==0) cnt++;
    }
    cout<<cnt<<"\n";
    return 0;
}
