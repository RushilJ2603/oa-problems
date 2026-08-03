#include <bits/stdc++.h>
using namespace std;
using ll = long long;

ll solve(int n, const vector<vector<pair<int, ll>>>& g) {
    const ll INF = LLONG_MAX / 4;
    vector<ll> d1(n + 1, INF), d2(n + 1, INF);
    priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<pair<ll, int>>> pq;
    d1[1] = 0;
    pq.push({0, 1});
    while (!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();
        if (d > d2[u]) continue;
        for (auto [v, w] : g[u]) {
            ll nd = d + w;
            if (nd < d1[v]) {
                if (d1[v] < d2[v]) {
                    d2[v] = d1[v];
                    pq.push({d2[v], v});
                }
                d1[v] = nd;
                pq.push({nd, v});
            } else if (nd > d1[v] && nd < d2[v]) {
                d2[v] = nd;
                pq.push({nd, v});
            }
        }
    }
    return d2[n];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    if (!(cin >> n >> m)) return 0;
    vector<vector<pair<int, ll>>> g(n + 1);
    for (int i = 0; i < m; i++) {
        int u, v;
        ll w;
        cin >> u >> v >> w;
        g[u].push_back({v, w});
        g[v].push_back({u, w});
    }
    cout << solve(n, g) << "\n";
    return 0;
}
