#include <bits/stdc++.h>
using namespace std;

long long solve(int m, int n, vector<vector<long long>>& grid) {
    vector<vector<long long>> dp = grid;
    for (int j = 1; j < n; ++j)
        dp[0][j] += dp[0][j - 1];
    for (int i = 1; i < m; ++i)
        dp[i][0] += dp[i - 1][0];
    for (int i = 1; i < m; ++i)
        for (int j = 1; j < n; ++j)
            dp[i][j] += max(dp[i - 1][j], dp[i][j - 1]);
    return dp[m - 1][n - 1];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int m, n;
    if (!(cin >> m >> n)) return 0;
    vector<vector<long long>> grid(m, vector<long long>(n));
    for (int i = 0; i < m; ++i)
        for (int j = 0; j < n; ++j)
            cin >> grid[i][j];
    cout << solve(m, n, grid) << "\n";
    return 0;
}
