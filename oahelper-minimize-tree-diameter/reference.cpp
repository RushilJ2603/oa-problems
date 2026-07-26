#include <bits/stdc++.h>
using namespace std;

int solve(int n, int k, vector<pair<int, int>>& edges) {
    int need = n - k;
    if (need < 1) need = 1;
    if (n <= 1 || need <= 1) return 0;

    vector<vector<int>> adj(n + 1);
    for (auto& e : edges) {
        adj[e.first].push_back(e.second);
        adj[e.second].push_back(e.first);
    }

    auto bfs = [&](int src) {
        vector<int> dist(n + 1, -1);
        queue<int> q;
        q.push(src);
        dist[src] = 0;
        int far = src;
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            if (dist[u] > dist[far]) far = u;
            for (int v : adj[u]) {
                if (dist[v] < 0) {
                    dist[v] = dist[u] + 1;
                    q.push(v);
                }
            }
        }
        return make_pair(far, dist);
    };

    if (k == 0) {
        auto p1 = bfs(1);
        auto p2 = bfs(p1.first);
        return p2.second[p2.first];
    }

    vector<vector<int>> D(n + 1);
    for (int i = 1; i <= n; i++) D[i] = bfs(i).second;

    auto feasible = [&](int diam) {
        int R = diam / 2;
        for (int c = 1; c <= n; c++) {
            int cnt = 0;
            for (int i = 1; i <= n; i++)
                if (D[c][i] <= R) cnt++;
            if (cnt >= need) return true;
        }
        if (diam % 2 == 1) {
            for (auto& e : edges) {
                int u = e.first, v = e.second;
                int cnt = 0;
                for (int i = 1; i <= n; i++)
                    if (min(D[u][i], D[v][i]) <= R) cnt++;
                if (cnt >= need) return true;
            }
        }
        return false;
    };

    int lo = 0, hi = n - 1;
    while (lo < hi) {
        int mid = lo + (hi - lo) / 2;
        if (feasible(mid)) hi = mid;
        else lo = mid + 1;
    }
    return lo;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, k;
    if (!(cin >> n >> k)) return 0;
    vector<pair<int, int>> edges;
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        edges.push_back({u, v});
    }
    cout << solve(n, k, edges) << "\n";
    return 0;
}
