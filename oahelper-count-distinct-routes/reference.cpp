#include <bits/stdc++.h>
using namespace std;

const long long MOD = 1000000007LL;

long long solve(const string& plan, long long n, long long s, long long e) {
    int m = (int)plan.size();
    vector<int> nl(m + 1, -1), nr(m + 1, -1);
    for (int i = m - 1; i >= 0; --i) {
        nl[i] = nl[i + 1];
        nr[i] = nr[i + 1];
        if (plan[i] == 'l') nl[i] = i;
        else nr[i] = i;
    }

    vector<vector<long long>> layers(m + 1);
    layers[m].assign(n + 1, 0);
    layers[m][e] = 1;

    for (int i = m - 1; i >= 0; --i) {
        vector<long long> cur(n + 1, 0);
        cur[e] = 1;
        int jl = nl[i], jr = nr[i];
        if (jl >= 0) {
            const vector<long long>& dl = layers[jl + 1];
            for (long long p = 1; p <= n; ++p)
                cur[p] += dl[p - 1];
        }
        if (jr >= 0) {
            const vector<long long>& dr = layers[jr + 1];
            for (long long p = 0; p < n; ++p)
                cur[p] += dr[p + 1];
        }
        for (long long p = 0; p <= n; ++p)
            cur[p] %= MOD;
        layers[i] = move(cur);
    }
    return layers[0][s] % MOD;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    string plan;
    long long n, s, e;
    if (!(cin >> plan >> n >> s >> e)) return 0;
    cout << solve(plan, n, s, e) << "\n";
    return 0;
}
