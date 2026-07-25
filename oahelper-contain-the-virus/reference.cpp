#include <bits/stdc++.h>
using namespace std;

long long solve(int n, int m, vector<vector<int>> grid) {
    const int dr[4] = {1, -1, 0, 0};
    const int dc[4] = {0, 0, 1, -1};
    long long total = 0;

    while (true) {
        vector<vector<char>> seen(n, vector<char>(m, 0));
        vector<vector<pair<int, int>>> cellsList;
        vector<set<pair<int, int>>> threatList;
        vector<int> wallsList;

        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                if (grid[i][j] != 1 || seen[i][j]) continue;
                vector<pair<int, int>> cells;
                set<pair<int, int>> threat;
                int walls = 0;
                seen[i][j] = 1;
                queue<pair<int, int>> q;
                q.push({i, j});
                while (!q.empty()) {
                    auto [r, c] = q.front();
                    q.pop();
                    cells.push_back({r, c});
                    for (int d = 0; d < 4; ++d) {
                        int nr = r + dr[d], nc = c + dc[d];
                        if (nr < 0 || nr >= n || nc < 0 || nc >= m) continue;
                        if (grid[nr][nc] == 0) {
                            threat.insert({nr, nc});
                            ++walls;
                        } else if (grid[nr][nc] == 1 && !seen[nr][nc]) {
                            seen[nr][nc] = 1;
                            q.push({nr, nc});
                        }
                    }
                }
                cellsList.push_back(move(cells));
                threatList.push_back(move(threat));
                wallsList.push_back(walls);
            }
        }

        int best = -1;
        for (size_t k = 0; k < threatList.size(); ++k) {
            if (threatList[k].empty()) continue;
            if (best == -1 || threatList[k].size() > threatList[best].size())
                best = (int)k;
        }
        if (best == -1) break;

        total += wallsList[best];
        for (auto &pr : cellsList[best]) grid[pr.first][pr.second] = 2;
        for (size_t k = 0; k < threatList.size(); ++k) {
            if ((int)k == best || threatList[k].empty()) continue;
            for (auto &pr : threatList[k]) grid[pr.first][pr.second] = 1;
        }
    }
    return total;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    if (!(cin >> n >> m)) return 0;
    vector<vector<int>> grid(n, vector<int>(m));
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
            cin >> grid[i][j];
    cout << solve(n, m, grid) << "\n";
    return 0;
}
