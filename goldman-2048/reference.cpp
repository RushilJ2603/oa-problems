// 2048: 4x4 grid, N key presses (U/D/L/R). After each press, print the CUMULATIVE score
// (sum of all merged values so far). Merging: adjacent equal cells in the move direction combine
// once each; the merged value is added to the score.
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef array<ll,4> Row;
// Merge a length-4 line toward index 0. Returns score gained; writes result back.
ll mergeFront(Row &a){
    Row t{}; int k=0;
    for(int i=0;i<4;i++) if(a[i]) t[k++]=a[i];
    Row r{}; int j=0; ll gain=0;
    for(int i=0;i<k;i++){
        if(i+1<k && t[i]==t[i+1]){ ll m=t[i]*2; r[j++]=m; gain+=m; i++; }
        else r[j++]=t[i];
    }
    a=r; return gain;
}
int main(){
    ll g[4][4];
    for(int i=0;i<4;i++) for(int j=0;j<4;j++) cin>>g[i][j];
    int N; cin>>N;
    ll score=0;
    string out;
    for(int q=0;q<N;q++){
        string key; cin>>key; char c=toupper(key[0]);
        if(c=='L'){ for(int i=0;i<4;i++){ Row a={g[i][0],g[i][1],g[i][2],g[i][3]}; score+=mergeFront(a); for(int j=0;j<4;j++)g[i][j]=a[j]; } }
        else if(c=='R'){ for(int i=0;i<4;i++){ Row a={g[i][3],g[i][2],g[i][1],g[i][0]}; score+=mergeFront(a); for(int j=0;j<4;j++)g[i][3-j]=a[j]; } }
        else if(c=='U'){ for(int j=0;j<4;j++){ Row a={g[0][j],g[1][j],g[2][j],g[3][j]}; score+=mergeFront(a); for(int i=0;i<4;i++)g[i][j]=a[i]; } }
        else if(c=='D'){ for(int j=0;j<4;j++){ Row a={g[3][j],g[2][j],g[1][j],g[0][j]}; score+=mergeFront(a); for(int i=0;i<4;i++)g[3-i][j]=a[i]; } }
        out += to_string(score); out += "\n";
    }
    cout<<out;
    return 0;
}
