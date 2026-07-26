#include <bits/stdc++.h>
using namespace std;

struct DSU {
    vector<int> parent, rankv;
    int components;
    DSU(int n) : parent(n + 1), rankv(n + 1, 0), components(n) {
        iota(parent.begin(), parent.end(), 0);
    }
    int find(int x) {
        while (parent[x] != x) {
            parent[x] = parent[parent[x]];
            x = parent[x];
        }
        return x;
    }
    bool unite(int a, int b) {
        a = find(a);
        b = find(b);
        if (a == b) return false;
        if (rankv[a] < rankv[b]) swap(a, b);
        parent[b] = a;
        if (rankv[a] == rankv[b]) ++rankv[a];
        --components;
        return true;
    }
};

struct Edge {
    int u, v;
    long long w;
};

long long solve(int n, int m, vector<int>& U, vector<int>& V, vector<long long>& W) {
    if (n == 0) return 0;

    DSU dsu(n);
    vector<Edge> nonNeg;
    nonNeg.reserve(m);
    long long totalWeight = 0;
    long long keptWeight = 0;

    for (int i = 0; i < m; ++i) {
        int u = U[i], v = V[i];
        long long w = W[i];
        totalWeight += w;
        if (w < 0) {
            keptWeight += w;
            dsu.unite(u, v);
        } else {
            nonNeg.push_back({u, v, w});
        }
    }

    sort(nonNeg.begin(), nonNeg.end(), [](const Edge& a, const Edge& b) {
        return a.w < b.w;
    });

    for (const auto& e : nonNeg) {
        if (dsu.unite(e.u, e.v)) {
            keptWeight += e.w;
        }
    }

    if (dsu.components != 1) return -1;
    return totalWeight - keptWeight;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    if (!(cin >> n >> m)) return 0;
    vector<int> u(m), v(m);
    vector<long long> w(m);
    for (int i = 0; i < m; i++) cin >> u[i] >> v[i] >> w[i];
    cout << solve(n, m, u, v, w) << "\n";
    return 0;
}
