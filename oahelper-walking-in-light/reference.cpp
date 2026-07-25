#include <bits/stdc++.h>
using namespace std;

struct DSU {
    vector<int> p;
    DSU(int n) : p(n) { iota(p.begin(), p.end(), 0); }
    int find(int i) { return p[i] == i ? i : p[i] = find(p[i]); }
    void unite(int a, int b) {
        a = find(a); b = find(b);
        if (a != b) p[a] = b;
    }
};

string solve(int n, vector<long double>& x, vector<long double>& y,
             vector<long double>& r, long double xs, long double ys,
             long double xt, long double yt) {
    const long double EPS = 1e-9L;
    DSU dsu(n);
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            long double dx = x[i] - x[j], dy = y[i] - y[j];
            if (hypotl(dx, dy) <= r[i] + r[j] + EPS) dsu.unite(i, j);
        }
    }
    vector<int> S, T;
    for (int i = 0; i < n; i++) {
        if (hypotl(x[i] - xs, y[i] - ys) <= r[i] + EPS) S.push_back(i);
        if (hypotl(x[i] - xt, y[i] - yt) <= r[i] + EPS) T.push_back(i);
    }
    for (int u : S)
        for (int v : T)
            if (dsu.find(u) == dsu.find(v)) return "YES";
    return "NO";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    if (!(cin >> n)) return 0;
    vector<long double> x(n), y(n), r(n);
    for (int i = 0; i < n; i++) cin >> x[i] >> y[i] >> r[i];
    long double xs, ys, xt, yt;
    cin >> xs >> ys >> xt >> yt;
    cout << solve(n, x, y, r, xs, ys, xt, yt) << "\n";
    return 0;
}
