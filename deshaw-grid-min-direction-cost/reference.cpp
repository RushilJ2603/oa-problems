#include <bits/stdc++.h>
using namespace std;

// 0/1 BFS: moving along a cell's own arrow costs 0, any other of the 4 neighbours costs 1.
int minCost(int m, int n, const vector<string>& g) {
    auto arrow = [&](char c) -> pair<int,int> {
        if (c == 'U') return {-1, 0};
        if (c == 'D') return {1, 0};
        if (c == 'L') return {0, -1};
        return {0, 1};                       // 'R'
    };
    const int dr[4] = {-1, 1, 0, 0}, dc[4] = {0, 0, -1, 1};
    vector<vector<int>> dist(m, vector<int>(n, INT_MAX));
    deque<pair<int,int>> dq;
    dist[0][0] = 0;
    dq.push_front({0, 0});
    while (!dq.empty()) {
        auto [r, c] = dq.front(); dq.pop_front();
        auto pd = arrow(g[r][c]);
        for (int k = 0; k < 4; k++) {
            int nr = r + dr[k], nc = c + dc[k];
            if (nr < 0 || nr >= m || nc < 0 || nc >= n) continue;
            int w = (dr[k] == pd.first && dc[k] == pd.second) ? 0 : 1;
            if (dist[r][c] + w < dist[nr][nc]) {
                dist[nr][nc] = dist[r][c] + w;
                if (w == 0) dq.push_front({nr, nc});
                else dq.push_back({nr, nc});
            }
        }
    }
    return dist[m-1][n-1];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int m, n;
    if (!(cin >> m >> n)) return 0;
    vector<string> g(m);
    for (auto& s : g) cin >> s;
    cout << minCost(m, n, g) << "\n";
    return 0;
}
