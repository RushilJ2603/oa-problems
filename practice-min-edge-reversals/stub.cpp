#include <bits/stdc++.h>
using namespace std;

// Return the minimum number of edge reversals to get from s to t, or -1 if impossible.
// adj[u] holds the directed edges u -> v.
int minReversals(int n, vector<pair<int,int>>& edges, int s, int t) {
    // WRITE YOUR CODE HERE
    return -1;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    if (!(cin >> n >> m)) return 0;
    vector<pair<int,int>> edges(m);
    for (auto& e : edges) cin >> e.first >> e.second;
    int s, t; cin >> s >> t;
    cout << minReversals(n, edges, s, t) << "\n";
    return 0;
}
