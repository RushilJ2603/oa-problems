#include <bits/stdc++.h>
using namespace std;

int solve(int n, int m, vector<vector<int>> g) {
    int dx[4] = {1, -1, 0, 0};
    int dy[4] = {0, 0, 1, -1};
    long long walls = 0;
    while (true) {
        vector<vector<char>> seen(n, vector<char>(m, 0));
        vector<vector<pair<int, int>>> cells;
        vector<set<pair<int, int>>> thr;
        vector<int> wc;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (g[i][j] == 1 && !seen[i][j]) {
                    queue<pair<int, int>> q;
                    q.push({i, j});
                    seen[i][j] = 1;
                    vector<pair<int, int>> cs;
                    set<pair<int, int>> th;
                    int w = 0;
                    while (!q.empty()) {
                        auto [x, y] = q.front();
                        q.pop();
                        cs.push_back({x, y});
                        for (int d = 0; d < 4; d++) {
                            int a = x + dx[d], b = y + dy[d];
                            if (a < 0 || a >= n || b < 0 || b >= m) continue;
                            if (g[a][b] == 0) {
                                th.insert({a, b});
                                w++;
                            } else if (g[a][b] == 1 && !seen[a][b]) {
                                seen[a][b] = 1;
                                q.push({a, b});
                            }
                        }
                    }
                    if (!th.empty()) {
                        cells.push_back(cs);
                        thr.push_back(th);
                        wc.push_back(w);
                    }
                }
            }
        }
        if (cells.empty()) break;
        int pick = 0;
        for (size_t i = 1; i < cells.size(); i++) {
            if (thr[i].size() > thr[pick].size() ||
                (thr[i].size() == thr[pick].size() && wc[i] < wc[pick]))
                pick = (int)i;
        }
        walls += wc[pick];
        for (auto [x, y] : cells[pick]) g[x][y] = 2;
        for (size_t i = 0; i < cells.size(); i++) {
            if ((int)i == pick) continue;
            for (auto [x, y] : thr[i]) g[x][y] = 1;
        }
    }
    return (int)walls;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    if (!(cin >> n >> m)) return 0;
    vector<vector<int>> g(n, vector<int>(m));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++) cin >> g[i][j];
    cout << solve(n, m, g) << "\n";
    return 0;
}
