#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9;

bool bfs(int n, const vector<vector<int>>& adj, const vector<int>& pairU,
         const vector<int>& pairV, vector<int>& dist) {
    queue<int> q;
    for (int u = 1; u <= n; u++) {
        if (pairU[u] == 0) {
            dist[u] = 0;
            q.push(u);
        } else {
            dist[u] = INF;
        }
    }
    dist[0] = INF;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        if (dist[u] < dist[0]) {
            for (int v : adj[u]) {
                if (dist[pairV[v]] == INF) {
                    dist[pairV[v]] = dist[u] + 1;
                    q.push(pairV[v]);
                }
            }
        }
    }
    return dist[0] != INF;
}

bool dfs(int u, const vector<vector<int>>& adj, vector<int>& pairU,
         vector<int>& pairV, vector<int>& dist) {
    if (u != 0) {
        for (int v : adj[u]) {
            if (dist[pairV[v]] == dist[u] + 1) {
                if (dfs(pairV[v], adj, pairU, pairV, dist)) {
                    pairV[v] = u;
                    pairU[u] = v;
                    return true;
                }
            }
        }
        dist[u] = INF;
        return false;
    }
    return true;
}

int solve(int n, vector<pair<int, int>>& houses) {
    if (n <= 0) return 0;
    sort(houses.begin(), houses.end());
    houses.erase(unique(houses.begin(), houses.end()), houses.end());

    vector<int> Xs, Ys;
    for (auto& p : houses) {
        Xs.push_back(p.first);
        Ys.push_back(p.second);
    }
    sort(Xs.begin(), Xs.end());
    Xs.erase(unique(Xs.begin(), Xs.end()), Xs.end());
    sort(Ys.begin(), Ys.end());
    Ys.erase(unique(Ys.begin(), Ys.end()), Ys.end());

    int R = (int)Xs.size(), C = (int)Ys.size();
    vector<vector<int>> adj(R + 1);
    for (auto& p : houses) {
        int u = (int)(lower_bound(Xs.begin(), Xs.end(), p.first) - Xs.begin()) + 1;
        int v = (int)(lower_bound(Ys.begin(), Ys.end(), p.second) - Ys.begin()) + 1;
        adj[u].push_back(v);
    }

    vector<int> pairU(R + 1, 0), pairV(C + 1, 0), dist(R + 1, 0);
    int result = 0;
    while (bfs(R, adj, pairU, pairV, dist)) {
        for (int u = 1; u <= R; u++) {
            if (pairU[u] == 0 && dfs(u, adj, pairU, pairV, dist)) {
                result++;
            }
        }
    }
    return result;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    if (!(cin >> n)) return 0;
    vector<pair<int, int>> houses(n);
    for (int i = 0; i < n; i++) cin >> houses[i].first >> houses[i].second;
    cout << solve(n, houses) << "\n";
    return 0;
}
