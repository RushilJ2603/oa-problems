#include <bits/stdc++.h>
using namespace std;

int getRich(long long initialEnergy, vector<int>& energy, vector<int>& coins) {
    int n = energy.size();
    long long cappedInitial = min(initialEnergy, (long long)n);
    
    vector<int> dp(n + 1, -1);
    dp[cappedInitial] = 0;
    
    int ans = 0;
    for (int i = 0; i < n; i++) {
        vector<int> next_dp(n + 1, -1);
        for (int e = 0; e <= n; e++) {
            if (dp[e] != -1) {
                ans = max(ans, dp[e] + coins[i]);
                
                int nxt_e1 = min(n, e + energy[i]);
                if (nxt_e1 - 1 >= 0) {
                    next_dp[nxt_e1 - 1] = max(next_dp[nxt_e1 - 1], dp[e]);
                }
                
                int nxt_e2 = e;
                if (nxt_e2 - 1 >= 0) {
                    next_dp[nxt_e2 - 1] = max(next_dp[nxt_e2 - 1], dp[e] + coins[i]);
                }
            }
        }
        dp = next_dp;
    }
    
    return ans;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    long long initialEnergy;
    if (!(cin >> initialEnergy)) return 0;
    int n; cin >> n;
    vector<int> energy(n);
    for (int i = 0; i < n; i++) cin >> energy[i];
    int m; cin >> m;
    vector<int> coins(m);
    for (int i = 0; i < m; i++) cin >> coins[i];
    cout << getRich(initialEnergy, energy, coins) << "\n";
    return 0;
}
