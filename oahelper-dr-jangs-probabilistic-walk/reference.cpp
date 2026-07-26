#include <bits/stdc++.h>
using namespace std;

// Returns (best_division, probability). best_division == 0 means not in any division.
pair<int, double> solve(int N, int T, const vector<vector<pair<int, double>>>& adj) {
    vector<double> cur(N + 1, 0.0);
    cur[1] = 1.0;
    int steps = T / 10;
    for (int s = 0; s < steps; ++s) {
        vector<double> nxt(N + 1, 0.0);
        for (int u = 1; u <= N; ++u) {
            if (cur[u] == 0.0) continue;
            for (auto [v, p] : adj[u]) {
                nxt[v] += cur[u] * p;
            }
            // terminal: probability vanishes
        }
        cur.swap(nxt);
    }
    int best = 0;
    double max_p = -1.0;
    for (int i = 1; i <= N; ++i) {
        if (cur[i] > max_p + 1e-9) {
            max_p = cur[i];
            best = i;
        }
    }
    if (max_p < 1e-9) return {0, 0.0};
    return {best, max_p};
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int N, E, T;
    int tc = 1;
    cout << fixed << setprecision(6);
    while (cin >> N >> E >> T) {
        vector<vector<pair<int, double>>> adj(N + 1);
        for (int i = 0; i < E; ++i) {
            int u, v;
            double p;
            cin >> u >> v >> p;
            adj[u].push_back({v, p});
        }
        auto [best, max_p] = solve(N, T, adj);
        cout << "#" << tc++;
        if (best == 0) {
            cout << " 0\n";
        } else {
            cout << " " << best << " " << max_p << "\n";
        }
    }
    return 0;
}
