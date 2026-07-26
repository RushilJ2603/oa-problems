#include <bits/stdc++.h>
using namespace std;

// 2D prefix sums + binary search on the side length. Feasibility ("some L x L square has sum <= k")
// is monotone in L because all values are non-negative, so binary search is valid.
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int m, n;
    long long k;
    if (!(cin >> m >> n >> k)) return 0;
    vector<vector<long long>> p(m + 1, vector<long long>(n + 1, 0));
    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++) {
            long long x; cin >> x;
            p[i + 1][j + 1] = x + p[i][j + 1] + p[i + 1][j] - p[i][j];
        }
    auto square = [&](int r, int c, int L) -> long long {
        return p[r + L][c + L] - p[r][c + L] - p[r + L][c] + p[r][c];
    };
    auto feasible = [&](int L) -> bool {
        if (L == 0) return true;
        for (int r = 0; r + L <= m; r++)
            for (int c = 0; c + L <= n; c++)
                if (square(r, c, L) <= k) return true;
        return false;
    };
    int lo = 0, hi = min(m, n), ans = 0;
    while (lo <= hi) {
        int mid = (lo + hi) / 2;
        if (feasible(mid)) { ans = mid; lo = mid + 1; }
        else hi = mid - 1;
    }
    cout << ans << "\n";
    return 0;
}
