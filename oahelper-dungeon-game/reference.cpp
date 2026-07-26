#include <bits/stdc++.h>
using namespace std;

int solve(int m, int n, vector<vector<int>>& dungeon) {
    vector<vector<int>> dp(m, vector<int>(n));
    for (int i = m - 1; i >= 0; --i) {
        for (int j = n - 1; j >= 0; --j) {
            if (i == m - 1 && j == n - 1) {
                dp[i][j] = max(1, 1 - dungeon[i][j]);
            } else if (i == m - 1) {
                dp[i][j] = max(1, dp[i][j + 1] - dungeon[i][j]);
            } else if (j == n - 1) {
                dp[i][j] = max(1, dp[i + 1][j] - dungeon[i][j]);
            } else {
                int min_next = min(dp[i + 1][j], dp[i][j + 1]);
                dp[i][j] = max(1, min_next - dungeon[i][j]);
            }
        }
    }
    return dp[0][0];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int m, n;
    if (!(cin >> m >> n)) return 0;
    vector<vector<int>> dungeon(m, vector<int>(n));
    for (int i = 0; i < m; ++i)
        for (int j = 0; j < n; ++j)
            cin >> dungeon[i][j];
    cout << solve(m, n, dungeon) << "\n";
    return 0;
}
