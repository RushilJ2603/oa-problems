#include <bits/stdc++.h>
using namespace std;

// Topological (Kahn) DP. The producer is node 0 and forwards 2 bits on each outgoing edge; every
// other node forwards (bits it received) + 1 on each outgoing edge. A node's received count is the
// sum of what all its in-edges carry. The answer is the total received by all sink nodes.
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    if (!(cin >> n >> m)) return 0;
    vector<vector<int>> adj(n);
    vector<int> indeg(n, 0), outdeg(n, 0);
    for (int i = 0; i < m; i++) {
        int u, v; cin >> u >> v;
        adj[u].push_back(v);
        indeg[v]++; outdeg[u]++;
    }
    vector<long long> received(n, 0), forwarded(n, 0);
    vector<int> ind = indeg;
    queue<int> q;
    for (int i = 0; i < n; i++) if (ind[i] == 0) q.push(i);
    while (!q.empty()) {
        int u = q.front(); q.pop();
        forwarded[u] = (u == 0) ? 2 : received[u] + 1;
        for (int v : adj[u]) {
            received[v] += forwarded[u];
            if (--ind[v] == 0) q.push(v);
        }
    }
    long long ans = 0;
    for (int i = 0; i < n; i++) if (outdeg[i] == 0) ans += received[i];
    cout << ans << "\n";
    return 0;
}
