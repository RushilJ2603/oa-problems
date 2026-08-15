#include <bits/stdc++.h>
using namespace std;

vector<string> classifyEdges(int g_nodes, vector<int>& g_from, vector<int>& g_to, vector<int>& g_weight) {
    int n = g_nodes;
    int m = g_from.size();
    vector<vector<pair<int, long long>>> adj(n + 1);
    for (int i = 0; i < m; i++) {
        adj[g_from[i]].push_back({g_to[i], g_weight[i]});
        adj[g_to[i]].push_back({g_from[i], g_weight[i]});
    }

    auto dijkstra = [&](int start, vector<long long>& dist) {
        dist.assign(n + 1, 1e18);
        priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>> pq;
        dist[start] = 0;
        pq.push({0, start});
        while (!pq.empty()) {
            auto [d, u] = pq.top();
            pq.pop();
            if (d > dist[u]) continue;
            for (auto& edge : adj[u]) {
                int v = edge.first;
                long long w = edge.second;
                if (dist[u] + w < dist[v]) {
                    dist[v] = dist[u] + w;
                    pq.push({dist[v], v});
                }
            }
        }
    };

    vector<long long> dist1, distN;
    dijkstra(1, dist1);
    dijkstra(n, distN);

    long long shortest = dist1[n];
    vector<string> res(m, "NO");
    if (shortest == 1e18) return res;

    for (int i = 0; i < m; i++) {
        int u = g_from[i];
        int v = g_to[i];
        long long w = g_weight[i];
        if (dist1[u] + w + distN[v] == shortest || dist1[v] + w + distN[u] == shortest) {
            res[i] = "YES";
        }
    }
    return res;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int g_nodes, g_edges;
    if (!(cin >> g_nodes >> g_edges)) return 0;
    vector<int> g_from(g_edges), g_to(g_edges), g_weight(g_edges);
    for (int i = 0; i < g_edges; i++) {
        cin >> g_from[i] >> g_to[i] >> g_weight[i];
    }
    vector<string> res = classifyEdges(g_nodes, g_from, g_to, g_weight);
    for (const string& s : res) cout << s << "\n";
    return 0;
}
