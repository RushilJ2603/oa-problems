#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int m, n;
    if (!(cin >> m)) return 0;
    if (!(cin >> n)) return 0;
    int total = m * n;
    vector<long long> a(total);
    for (int i = 0; i < total; ++i) cin >> a[i];

    // Process cells in decreasing value order so longer paths from
    // larger neighbours are already finalized (DAG DP sweep).
    vector<int> order(total);
    iota(order.begin(), order.end(), 0);
    sort(order.begin(), order.end(), [&](int p, int q) {
        return a[p] > a[q];
    });

    vector<int> dp(total, 1);
    int best = 1;
    for (int idx : order) {
        int i = idx / n, j = idx % n;
        long long v = a[idx];
        int cur = 1;
        if (i > 0 && a[idx - n] > v) cur = max(cur, 1 + dp[idx - n]);
        if (i + 1 < m && a[idx + n] > v) cur = max(cur, 1 + dp[idx + n]);
        if (j > 0 && a[idx - 1] > v) cur = max(cur, 1 + dp[idx - 1]);
        if (j + 1 < n && a[idx + 1] > v) cur = max(cur, 1 + dp[idx + 1]);
        dp[idx] = cur;
        if (cur > best) best = cur;
    }
    cout << best << "\n";
    return 0;
}
