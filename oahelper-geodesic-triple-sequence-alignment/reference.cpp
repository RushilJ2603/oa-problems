#include <bits/stdc++.h>
using namespace std;

long long solve(int n, int m, int k,
                const vector<long long>& X,
                const vector<long long>& Y,
                const vector<long long>& Z) {
    const long long INF = (long long)4e18;
    auto dist = [](long long a, long long b) { return llabs(a - b); };

    vector<vector<vector<long long>>> dp(
        n + 1, vector<vector<long long>>(m + 1, vector<long long>(k + 1, INF)));
    dp[0][0][0] = 0;

    for (int i = 0; i <= n; ++i) {
        for (int j = 0; j <= m; ++j) {
            for (int l = 0; l <= k; ++l) {
                if (dp[i][j][l] >= INF) continue;
                long long cur = dp[i][j][l];
                if (i + 1 <= n)
                    dp[i + 1][j][l] = min(dp[i + 1][j][l], cur + 1);
                if (j + 1 <= m)
                    dp[i][j + 1][l] = min(dp[i][j + 1][l], cur + 1);
                if (l + 1 <= k)
                    dp[i][j][l + 1] = min(dp[i][j][l + 1], cur + 1);
                if (i + 1 <= n && j + 1 <= m)
                    dp[i + 1][j + 1][l] =
                        min(dp[i + 1][j + 1][l], cur + dist(X[i], Y[j]) + 1);
                if (i + 1 <= n && l + 1 <= k)
                    dp[i + 1][j][l + 1] =
                        min(dp[i + 1][j][l + 1], cur + dist(X[i], Z[l]) + 1);
                if (j + 1 <= m && l + 1 <= k)
                    dp[i][j + 1][l + 1] =
                        min(dp[i][j + 1][l + 1], cur + dist(Y[j], Z[l]) + 1);
                if (i + 1 <= n && j + 1 <= m && l + 1 <= k) {
                    long long t = dist(X[i], Y[j]) + dist(Y[j], Z[l]) + dist(X[i], Z[l]);
                    dp[i + 1][j + 1][l + 1] = min(dp[i + 1][j + 1][l + 1], cur + t);
                }
            }
        }
    }
    return dp[n][m][k];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m, k;
    if (!(cin >> n >> m >> k)) return 0;
    vector<long long> X(n), Y(m), Z(k);
    for (int i = 0; i < n; ++i) cin >> X[i];
    for (int i = 0; i < m; ++i) cin >> Y[i];
    for (int i = 0; i < k; ++i) cin >> Z[i];
    cout << solve(n, m, k, X, Y, Z) << "\n";
    return 0;
}
