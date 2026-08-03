#include <bits/stdc++.h>
using namespace std;

int solve(const string& series) {
    int n = (int)series.size();
    if (n == 0) return 0;
    vector<vector<int>> dp(n, vector<int>(n, 0));
    for (int i = 0; i < n; i++) dp[i][i] = 1;
    for (int len = 2; len <= n; len++) {
        for (int left = 0; left + len <= n; left++) {
            int right = left + len - 1;
            int best = 1 + dp[left + 1][right];
            for (int mid = left + 1; mid <= right; mid++) {
                if (series[mid] == series[left]) {
                    int cost = dp[mid][right];
                    if (mid > left + 1) cost += dp[left + 1][mid - 1];
                    if (cost < best) best = cost;
                }
            }
            dp[left][right] = best;
        }
    }
    return dp[0][n - 1];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    string series;
    if (!(cin >> series)) return 0;
    cout << solve(series) << "\n";
    return 0;
}
