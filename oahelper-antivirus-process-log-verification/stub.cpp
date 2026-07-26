#include <bits/stdc++.h>
using namespace std;

string solve(int n, vector<vector<int>>& adj, int q, vector<vector<int>>& queries) {
    // WRITE YOUR CODE HERE
    return string(q, '0');
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    if (!(cin >> n)) return 0;
    vector<vector<int>> adj(n + 1);
    for (int i = 0; i < n - 1; ++i) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    int q;
    cin >> q;
    vector<vector<int>> queries(q, vector<int>(n));
    for (int i = 0; i < q; ++i)
        for (int j = 0; j < n; ++j) cin >> queries[i][j];
    cout << solve(n, adj, q, queries) << "\n";
    return 0;
}
