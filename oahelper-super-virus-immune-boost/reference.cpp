#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct Dinic {
    struct E { int to; ll cap; };
    vector<E> es;
    vector<vector<int>> g;
    vector<int> level, it;
    int n;
    Dinic(int n_) : g(n_), level(n_), it(n_), n(n_) {}
    void add(int u, int v, ll c) {
        g[u].push_back((int)es.size()); es.push_back({v, c});
        g[v].push_back((int)es.size()); es.push_back({u, 0});
    }
    bool bfs(int s, int t) {
        fill(level.begin(), level.end(), -1);
        queue<int> q; level[s] = 0; q.push(s);
        while (!q.empty()) {
            int u = q.front(); q.pop();
            for (int id : g[u]) {
                if (es[id].cap > 0 && level[es[id].to] < 0) {
                    level[es[id].to] = level[u] + 1;
                    q.push(es[id].to);
                }
            }
        }
        return level[t] >= 0;
    }
    ll dfs(int u, int t, ll f) {
        if (u == t) return f;
        for (int &k = it[u]; k < (int)g[u].size(); k++) {
            int id = g[u][k];
            int v = es[id].to;
            if (es[id].cap > 0 && level[v] == level[u] + 1) {
                ll d = dfs(v, t, min(f, es[id].cap));
                if (d > 0) { es[id].cap -= d; es[id ^ 1].cap += d; return d; }
            }
        }
        return 0;
    }
    ll maxflow(int s, int t) {
        ll flow = 0;
        while (bfs(s, t)) {
            fill(it.begin(), it.end(), 0);
            ll f;
            while ((f = dfs(s, t, LLONG_MAX / 4)) > 0) flow += f;
        }
        return flow;
    }
};

long long solve(int x, vector<long long>& boost, vector<pair<int,int>>& pre) {
    int S = 0, T = x + 1;
    Dinic din(x + 2);
    const ll INF = LLONG_MAX / 8;
    ll pos = 0;
    for (int i = 1; i <= x; i++) {
        if (boost[i] > 0) { pos += boost[i]; din.add(S, i, boost[i]); }
        else if (boost[i] < 0) din.add(i, T, -boost[i]);
    }
    for (auto &e : pre) din.add(e.first, e.second, INF);
    return pos - din.maxflow(S, T);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int x;
    if (!(cin >> x)) return 0;
    vector<ll> boost(x + 1, 0);
    vector<pair<int,int>> pre;
    for (int i = 1; i <= x; i++) {
        ll b; int m;
        cin >> b >> m;
        boost[i] = b;
        for (int j = 0; j < m; j++) {
            int p; cin >> p;
            pre.push_back({i, p});
        }
    }
    cout << solve(x, boost, pre) << "\n";
    return 0;
}
