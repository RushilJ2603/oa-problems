#include <bits/stdc++.h>
using namespace std;

bool can_add_edge(int n, const vector<vector<int>>& adj,
                  const set<pair<int,int>>& present, int a, int b) {
    if (present.count({a, b})) {
        return false;
    }
    // Cycle via a->b exists iff b already reaches a (incl. a==b).
    vector<int> stack;
    vector<char> seen(n, 0);
    stack.push_back(b);
    seen[b] = 1;
    while (!stack.empty()) {
        int u = stack.back();
        stack.pop_back();
        if (u == a) {
            return false;
        }
        for (int v : adj[u]) {
            if (!seen[v]) {
                seen[v] = 1;
                stack.push_back(v);
            }
        }
    }
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    if (!(cin >> n >> m)) return 0;
    vector<vector<int>> adj(n);
    set<pair<int,int>> present;
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        present.insert({u, v});
    }
    int a, b;
    if (!(cin >> a >> b)) return 0;
    cout << (can_add_edge(n, adj, present, a, b) ? "true" : "false") << "\n";
    return 0;
}
