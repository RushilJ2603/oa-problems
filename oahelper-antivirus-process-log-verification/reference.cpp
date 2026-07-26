#include <bits/stdc++.h>
using namespace std;

string solve(int n, vector<vector<int>>& adj, int q, vector<vector<int>>& queries) {
    string res;
    res.reserve(q);
    vector<int> visited(n + 1, 0), seen(n + 1, 0), stamp(n + 1, 0), qu(n);
    for (int t = 1; t <= q; ++t) {
        const vector<int>& order = queries[t - 1];
        bool ok = (order[0] == 1);
        if (ok) {
            for (int i = 0; i < n; ++i) {
                int x = order[i];
                if (x < 1 || x > n || seen[x] == t) {
                    ok = false;
                    break;
                }
                seen[x] = t;
            }
        }
        if (!ok) {
            res += '0';
            continue;
        }
        fill(visited.begin(), visited.end(), 0);
        visited[1] = 1;
        int head = 0, tail = 0, pos = 1;
        qu[tail++] = 1;
        while (head < tail && ok) {
            int u = qu[head++];
            int c = 0;
            for (int v : adj[u])
                if (!visited[v]) ++c;
            if (pos + c > n) {
                ok = false;
                break;
            }
            for (int v : adj[u])
                if (!visited[v]) stamp[v] = t;
            for (int i = 0; i < c; ++i) {
                int v = order[pos + i];
                if (stamp[v] != t || visited[v]) {
                    ok = false;
                    break;
                }
                visited[v] = 1;
                qu[tail++] = v;
            }
            pos += c;
        }
        if (ok && pos != n) ok = false;
        res += ok ? '1' : '0';
    }
    return res;
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
