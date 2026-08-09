#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

// adj[u] holds pairs {neighbour, toll}. Junctions are numbered 1..n.
ll minTotalToll(int n, const vector<vector<pair<int, int>>> &adj, int a, int b, int c) {
    // WRITE YOUR CODE HERE
    return -1;
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

    cout << minTotalToll(n, adj, a, b, c) << "\n";
    return 0;
}
