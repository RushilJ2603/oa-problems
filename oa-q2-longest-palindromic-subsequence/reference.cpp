// Longest Palindromic Subsequence — classic interval DP. O(n^2).
#include <bits/stdc++.h>
using namespace std;
int main(){
    string s; if(!(cin>>s)) { cout<<0<<"\n"; return 0; }
    int n=s.size();
    vector<vector<int>> dp(n, vector<int>(n,0));
    for(int i=n-1;i>=0;--i){
        dp[i][i]=1;
        for(int j=i+1;j<n;++j){
            if(s[i]==s[j]) dp[i][j]=dp[i+1][j-1]+2;
            else dp[i][j]=max(dp[i+1][j], dp[i][j-1]);
        }
    }
    cout<<dp[0][n-1]<<"\n";
    return 0;
}
