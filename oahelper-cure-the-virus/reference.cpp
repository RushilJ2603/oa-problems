#include <bits/stdc++.h>
using namespace std;

struct Dinic {
    struct E { int to; long long cap; };
    vector<E> es;
    vector<vector<int>> head;
    vector<int> level, it;
    int n;
    Dinic(int n_) : head(n_), level(n_), it(n_), n(n_) {}
    void add(int u, int v, long long c) {
        head[u].push_back((int)es.size()); es.push_back({v, c});
        head[v].push_back((int)es.size()); es.push_back({u, 0});
    }
    bool bfs(int s, int t) {
        fill(level.begin(), level.end(), -1);
        queue<int> q; q.push(s); level[s] = 0;
        while (!q.empty()) {
            int u = q.front(); q.pop();
            for (int e : head[u]) {
                if (es[e].cap > 0 && level[es[e].to] < 0) {
                    level[es[e].to] = level[u] + 1;
                    q.push(es[e].to);
                }
            }
        }
        return level[t] >= 0;
    }
    long long dfs(int u, int t, long long f) {
        if (u == t) return f;
        for (; it[u] < (int)head[u].size(); it[u]++) {
            int e = head[u][it[u]];
            int v = es[e].to;
            if (es[e].cap > 0 && level[v] == level[u] + 1) {
                long long d = dfs(v, t, min(f, es[e].cap));
                if (d > 0) { es[e].cap -= d; es[e ^ 1].cap += d; return d; }
            }
        }
        level[u] = -1;
        return 0;
    }
    long long maxflow(int s, int t) {
        long long flow = 0;
        while (bfs(s, t)) {
            fill(it.begin(), it.end(), 0);
            long long f;
            while ((f = dfs(s, t, LLONG_MAX / 4)) > 0) flow += f;
        }
        return flow;
    }
};

long long solve(int n, vector<long long>& impact, vector<vector<int>>& precells) {
    int S = n, T = n + 1;
    Dinic din(n + 2);
    const long long INF = (long long)4e18 / 8;
    long long totalPos = 0;
    for (int i = 0; i < n; i++) {
        if (impact[i] > 0) { totalPos += impact[i]; din.add(S, i, impact[i]); }
        else if (impact[i] < 0) din.add(i, T, -impact[i]);
        for (int p : precells[i]) din.add(i, p, INF);
    }
    return totalPos - din.maxflow(S, T);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    if (!(cin >> n)) return 0;
    vector<long long> impact(n);
    vector<vector<int>> precells(n);
    for (int i = 0; i < n; i++) {
        int k;
        cin >> impact[i] >> k;
        precells[i].resize(k);
        for (int j = 0; j < k; j++) {
            cin >> precells[i][j];
            precells[i][j]--;
        }
    }
    cout << solve(n, impact, precells) << "\n";
    return 0;
}
