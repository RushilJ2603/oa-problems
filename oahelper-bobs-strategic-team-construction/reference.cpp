#include <bits/stdc++.h>
using namespace std;

long long solve(int n, int m, int k, vector<int>& salary, vector<long long>& earning) {
    k = min(k, n);
    vector<vector<long long>> dp(m + 1, vector<long long>(k + 1, 0));
    for (int i = 0; i < n; ++i) {
        int sal = salary[i];
        long long earn = earning[i];
        int half = sal / 2;
        for (int j = m; j >= 0; --j) {
            for (int c = k; c >= 0; --c) {
                long long ans = dp[j][c];
                if (j >= sal) ans = max(ans, dp[j - sal][c] + earn);
                if (c >= 1 && j >= half) ans = max(ans, dp[j - half][c - 1] + earn);
                dp[j][c] = ans;
            }
        }
    }
    long long best = 0;
    for (int j = 0; j <= m; ++j)
        for (int c = 0; c <= k; ++c) best = max(best, dp[j][c]);
    return best;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m, k;
    if (!(cin >> n >> m >> k)) return 0;
    vector<int> salary(n);
    vector<long long> earning(n);
    for (int i = 0; i < n; ++i) cin >> salary[i];
    for (int i = 0; i < n; ++i) cin >> earning[i];
    cout << solve(n, m, k, salary, earning) << "\n";
    return 0;
}
