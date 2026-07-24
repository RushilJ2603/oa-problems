#include <bits/stdc++.h>
using namespace std;

// Count (ancestor u, descendant v) pairs with pathWeight(u, v) <= w[v]. Root = 0.
// w[i] = node weight; adj is the weighted adjacency list.
long long countGoodPairs(int n, const vector<long long>& w,
                         const vector<vector<pair<int, long long>>>& adj) {
    // WRITE YOUR CODE HERE
    return 0;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    if (!(cin >> n)) return 0;
    vector<long long> w(n);
    for (auto& x : w) cin >> x;
    vector<vector<pair<int, long long>>> adj(n);
    for (int i = 0; i < n - 1; ++i) {
        int a, b; long long c;
        cin >> a >> b >> c;
        adj[a].push_back({b, c});
        adj[b].push_back({a, c});
    }
    cout << countGoodPairs(n, w, adj) << "\n";
    return 0;
}
