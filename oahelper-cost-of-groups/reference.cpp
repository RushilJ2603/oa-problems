#include <bits/stdc++.h>
using namespace std;

long long group_cost(vector<long long>& g) {
    int m = (int)g.size();
    if (m < 2) return 0;
    sort(g.begin(), g.end());
    int k = m / 2;
    long long total = 0;
    for (int i = 0; i < k; i++) total += g[m - 1 - i] - g[i];
    return total;
}

long long solve(int n, vector<long long>& a, vector<pair<int, int>>& edges) {
    vector<vector<int>> adj(n + 1);
    for (auto& e : edges) {
        adj[e.first].push_back(e.second);
        adj[e.second].push_back(e.first);
    }
    vector<int> color(n + 1, -1);
    color[1] = 0;
    queue<int> q;
    q.push(1);
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int v : adj[u]) {
            if (color[v] == -1) {
                color[v] = color[u] ^ 1;
                q.push(v);
            }
        }
    }
    vector<long long> g0, g1;
    for (int i = 1; i <= n; i++) {
        if (color[i] == 0) g0.push_back(a[i - 1]);
        else g1.push_back(a[i - 1]);
    }
    return group_cost(g0) + group_cost(g1);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    if (!(cin >> T)) return 0;
    while (T--) {
        int n;
        cin >> n;
        vector<long long> a(n);
        for (int i = 0; i < n; i++) cin >> a[i];
        vector<pair<int, int>> edges;
        for (int i = 0; i < n - 1; i++) {
            int u, v;
            cin >> u >> v;
            edges.push_back({u, v});
        }
        cout << solve(n, a, edges) << "\n";
    }
    return 0;
}
