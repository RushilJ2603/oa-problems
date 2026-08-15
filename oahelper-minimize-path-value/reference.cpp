#include <bits/stdc++.h>
using namespace std;

struct Edge {
    int u, v, w;
    bool operator<(const Edge& o) const {
        return w < o.w;
    }
};

struct DSU {
    vector<int> p, sz;
    DSU(int n) : p(n), sz(n, 1) {
        iota(p.begin(), p.end(), 0);
    }
    int find(int x) {
        return p[x] == x ? x : p[x] = find(p[x]);
    }
    bool unite(int x, int y) {
        x = find(x); y = find(y);
        if (x == y) return false;
        if (sz[x] < sz[y]) swap(x, y);
        sz[x] += sz[y];
        p[y] = x;
        return true;
    }
};

long long solve(int n, int m, vector<int>& u, vector<int>& v, vector<int>& w, int src, int dest) {
    if (src == dest) return 0;
    vector<Edge> edges(m);
    for (int i = 0; i < m; i++) edges[i] = {u[i], v[i], w[i]};
    sort(edges.begin(), edges.end());
    DSU dsu(n + 1);
    for (auto& e : edges) {
        dsu.unite(e.u, e.v);
        if (dsu.find(src) == dsu.find(dest)) {
            return e.w;
        }
    }
    return -1;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    if (!(cin >> n >> m)) return 0;
    vector<int> u(m), v(m), w(m);
    for (int i = 0; i < m; i++) cin >> u[i] >> v[i] >> w[i];
    int src, dest;
    cin >> src >> dest;
    cout << solve(n, m, u, v, w, src, dest) << "\n";
    return 0;
}
