#include <bits/stdc++.h>
using namespace std;

int solve(int n, int k, vector<pair<int, int>>& edges) {
    // WRITE YOUR CODE HERE
    return 0;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, k;
    if (!(cin >> n >> k)) return 0;
    vector<pair<int, int>> edges;
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        edges.push_back({u, v});
    }
    cout << solve(n, k, edges) << "\n";
    return 0;
}
