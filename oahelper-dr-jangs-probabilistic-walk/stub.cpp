#include <bits/stdc++.h>
using namespace std;

pair<int, double> solve(int N, int T, const vector<vector<pair<int, double>>>& adj) {
    // WRITE YOUR CODE HERE
    return {0, 0.0};
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
