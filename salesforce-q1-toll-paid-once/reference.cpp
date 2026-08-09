#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

static const ll INF = (ll)4e18;

// Because a road is charged at most once, the total paid is the weight of the SET of distinct roads
// driven — so the task is to buy the cheapest set of roads that leaves a, b and c all connected.
// The cheapest such set is a tree with at most one branch point v, giving
//     answer = min over v of  d(a,v) + d(b,v) + d(c,v).
// Three Dijkstras, then one linear scan.
vector<ll> dijkstra(int n, const vector<vector<pair<int, int>>> &adj, int src) {
    vector<ll> dist(n + 1, INF);
    priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<pair<ll, int>>> pq;
    dist[src] = 0;
    pq.push({0, src});
    while (!pq.empty()) {
        pair<ll, int> top = pq.top();
        pq.pop();
        ll d = top.first;
        int u = top.second;
        if (d > dist[u]) continue;
        for (size_t i = 0; i < adj[u].size(); i++) {
            int v = adj[u][i].first;
            ll nd = d + (ll)adj[u][i].second;
            if (nd < dist[v]) {
                dist[v] = nd;
                pq.push({nd, v});
            }
        }
    }
    return dist;
}

ll minTotalToll(int n, const vector<vector<pair<int, int>>> &adj, int a, int b, int c) {
    vector<ll> da = dijkstra(n, adj, a);
    vector<ll> db = dijkstra(n, adj, b);
    vector<ll> dc = dijkstra(n, adj, c);

    ll best = INF;
    for (int v = 1; v <= n; v++) {
        if (da[v] == INF || db[v] == INF || dc[v] == INF) continue;
        ll cost = da[v] + db[v] + dc[v];
        if (cost < best) best = cost;
    }
    return best;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    if (!(cin >> n >> m)) return 0;
    vector<vector<pair<int, int>>> adj(n + 1);
    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    }
    int a, b, c;
    cin >> a >> b >> c;

    ll ans = minTotalToll(n, adj, a, b, c);
    cout << (ans >= INF ? -1 : ans) << "\n";
    return 0;
}
