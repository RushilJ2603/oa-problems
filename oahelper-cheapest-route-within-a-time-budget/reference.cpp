#include <bits/stdc++.h>
using namespace std;

long long solve(int n, int m, int maxTime, vector<int>& fee, vector<vector<int>>& edges, int src, int dest) {
    vector<vector<pair<int, int>>> adj(n);
    for (const auto& e : edges) {
        adj[e[0]].push_back({e[1], e[2]});
        adj[e[1]].push_back({e[0], e[2]});
    }

    // cost, u, time
    using State = tuple<long long, int, int>;
    priority_queue<State, vector<State>, greater<State>> pq;

    vector<int> min_time(n, maxTime + 1);

    pq.push({fee[src], src, 0});

    while (!pq.empty()) {
        auto [cost, u, t] = pq.top();
        pq.pop();

        if (t >= min_time[u]) continue;
        min_time[u] = t;

        if (u == dest) return cost;

        for (const auto& edge : adj[u]) {
            int v = edge.first;
            int t_edge = edge.second;
            int new_t = t + t_edge;
            if (new_t <= maxTime) {
                pq.push({cost + fee[v], v, new_t});
            }
        }
    }

    return -1;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n, m, maxTime;
    if (!(cin >> n >> m >> maxTime)) return 0;
    vector<int> fee(n);
    for (int i = 0; i < n; ++i) cin >> fee[i];
    vector<vector<int>> edges(m, vector<int>(3));
    for (int i = 0; i < m; ++i) {
        cin >> edges[i][0] >> edges[i][1] >> edges[i][2];
    }
    int src, dest;
    cin >> src >> dest;
    cout << solve(n, m, maxTime, fee, edges, src, dest) << "\n";
    return 0;
}
