#include <bits/stdc++.h>
using namespace std;

static const long long LIMIT = 100000000LL;
static const int INF = 1000000000;

int solve(int n, vector<long long>& a) {
    if (n <= 1) return 0;

    auto val = [&](int i, int changed) -> long long {
        return changed ? LIMIT : a[i];
    };

    vector<vector<int>> dp(2, vector<int>(2, INF));
    for (int c0 = 0; c0 < 2; ++c0)
        for (int c1 = 0; c1 < 2; ++c1)
            if (val(0, c0) + val(1, c1) >= 0)
                dp[c0][c1] = min(dp[c0][c1], c0 + c1);

    for (int i = 2; i < n; ++i) {
        vector<vector<int>> nd(2, vector<int>(2, INF));
        for (int cp = 0; cp < 2; ++cp)
            for (int cc = 0; cc < 2; ++cc) {
                if (dp[cp][cc] >= INF) continue;
                for (int cn = 0; cn < 2; ++cn) {
                    if (val(i - 1, cc) + val(i, cn) < 0) continue;
                    if (val(i - 2, cp) + val(i - 1, cc) + val(i, cn) < 0) continue;
                    nd[cc][cn] = min(nd[cc][cn], dp[cp][cc] + cn);
                }
            }
        dp = nd;
    }

    int best = INF;
    for (int i = 0; i < 2; ++i)
        for (int j = 0; j < 2; ++j)
            best = min(best, dp[i][j]);
    return best;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    if (!(cin >> n)) return 0;
    vector<long long> a(n);
    for (auto& x : a) cin >> x;
    cout << solve(n, a) << "\n";
    return 0;
}
