#include <bits/stdc++.h>
using namespace std;

vector<long long> solve(int n, vector<long long>& values, string state, int m) {
    vector<int> dist(n, -1);
    queue<int> q;
    for (int i = 0; i < n; ++i) {
        if (state[i] == '1') {
            dist[i] = 0;
            q.push(i);
        }
    }
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        if (u > 0 && dist[u - 1] == -1) {
            dist[u - 1] = dist[u] + 1;
            q.push(u - 1);
        }
        if (u + 1 < n && dist[u + 1] == -1) {
            dist[u + 1] = dist[u] + 1;
            q.push(u + 1);
        }
    }
    vector<long long> max_at(n, -1);
    for (int i = 0; i < n; ++i) {
        if (dist[i] != -1)
            max_at[dist[i]] = max(max_at[dist[i]], values[i]);
    }
    vector<long long> pref(n, -1);
    long long cur = -1;
    for (int d = 0; d < n; ++d) {
        cur = max(cur, max_at[d]);
        pref[d] = cur;
    }
    vector<long long> ans(m);
    for (int k = 0; k < m; ++k) {
        int idx = (k < n) ? k : n - 1;
        ans[k] = pref[idx];
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    if (!(cin >> n)) return 0;
    vector<long long> values(n);
    for (int i = 0; i < n; ++i) cin >> values[i];
    string state;
    cin >> state;
    int m;
    cin >> m;
    auto ans = solve(n, values, state, m);
    for (auto x : ans) cout << x << "\n";
    return 0;
}
