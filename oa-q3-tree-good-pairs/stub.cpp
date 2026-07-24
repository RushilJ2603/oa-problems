#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<long long> w(n);
    for (auto& x : w) cin >> x;
    vector<vector<pair<int,long long>>> adj(n);
    for (int i = 0; i < n - 1; ++i) {
        int a, b; long long c;
        cin >> a >> b >> c;
        adj[a].push_back({b, c});
        adj[b].push_back({a, c});
    }
    // Count (ancestor u, descendant v) pairs with pathWeight(u,v) <= w[v]. Root = 0.
    // your code here
    return 0;
}
