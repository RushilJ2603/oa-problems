#include <bits/stdc++.h>
using namespace std;

long long solve(int n, int k, vector<vector<long long>>& d) {
    for (int t = 0; t < n; t++)
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                if (d[i][t] + d[t][j] < d[i][j])
                    d[i][j] = d[i][t] + d[t][j];

    int size = 1 << n;
    const long long INF = (long long)4e18;
    vector<vector<long long>> mind(size);
    mind[0].assign(n, INF);
    vector<int> pc(size, 0);
    long long best = INF;

    for (int mask = 1; mask < size; mask++) {
        int low = mask & (-mask);
        int b = __builtin_ctz(low);
        pc[mask] = pc[mask ^ low] + 1;
        const vector<long long>& prev = mind[mask ^ low];
        vector<long long> cur(n);
        for (int i = 0; i < n; i++)
            cur[i] = min(prev[i], d[i][b]);
        if (pc[mask] <= k) {
            long long tot = 0;
            for (int i = 0; i < n; i++)
                if (!((mask >> i) & 1))
                    tot += cur[i];
            if (tot < best)
                best = tot;
        }
        mind[mask] = move(cur);
    }
    return best;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, k;
    if (!(cin >> n >> k)) return 0;
    vector<vector<long long>> cost(n, vector<long long>(n));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            cin >> cost[i][j];
    cout << solve(n, k, cost) << "\n";
    return 0;
}
