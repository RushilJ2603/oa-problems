#include <bits/stdc++.h>
using namespace std;

// 0-1 BFS: each original edge u->v is a weight-0 move u->v and a weight-1 move v->u (a reversal).
// Shortest path in {0,1} edge weights from s to t via a deque.
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    if (!(cin >> n >> m)) return 0;
    vector<vector<pair<int, int>>> adj(n + 1);
    for (int i = 0; i < m; i++) {
        int u, v; cin >> u >> v;
        adj[u].push_back({v, 0});   // travel with the edge, free
        adj[v].push_back({u, 1});   // travel against the edge, one reversal
    }
    int s, t; cin >> s >> t;
    const int INF = INT_MAX;
    vector<int> dist(n + 1, INF);
    deque<int> dq;
    dist[s] = 0; dq.push_back(s);
    while (!dq.empty()) {
        int u = dq.front(); dq.pop_front();
        for (auto [v, w] : adj[u]) {
            if (dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                if (w == 0) dq.push_front(v);
                else dq.push_back(v);
            }
        }
    }
    cout << (dist[t] == INF ? -1 : dist[t]) << "\n";
    return 0;
}
