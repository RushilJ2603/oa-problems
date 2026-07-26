#include <bits/stdc++.h>
using namespace std;

// n nodes (0..n-1); node 0 is the producer. `edges[i] = {u, v}` is a directed link u -> v.
// Return the total number of bits received by all sink nodes (nodes with no outgoing edge).
long long totalBitsAtSinks(int n, vector<pair<int,int>>& edges) {
    // WRITE YOUR CODE HERE
    return 0;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    if (!(cin >> n >> m)) return 0;
    vector<pair<int,int>> edges(m);
    for (auto& e : edges) cin >> e.first >> e.second;
    cout << totalBitsAtSinks(n, edges) << "\n";
    return 0;
}
