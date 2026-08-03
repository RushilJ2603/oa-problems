#include <bits/stdc++.h>
using namespace std;

string solve(int M, int N, vector<vector<int>>& grid, int startR, int startC, long long Z,
             const set<pair<int, int>>& safeCells) {
    if (safeCells.count({startR, startC}) && grid[startR][startC] > 0) {
        return to_string(Z);
    }
    queue<pair<int, int>> q;
    vector<vector<char>> visited(M, vector<char>(N, 0));
    int dr[4] = {-1, 1, 0, 0};
    int dc[4] = {0, 0, -1, 1};
    for (int i = 0; i < 4; i++) {
        int nr = startR + dr[i], nc = startC + dc[i];
        if (nr >= 0 && nr < M && nc >= 0 && nc < N && grid[nr][nc] == 0) {
            visited[nr][nc] = 1;
            q.push({nr, nc});
        }
    }
    long long minCost = LLONG_MAX;
    while (!q.empty()) {
        auto [r, c] = q.front();
        q.pop();
        for (int i = 0; i < 4; i++) {
            int nr = r + dr[i], nc = c + dc[i];
            if (nr < 0 || nr >= M || nc < 0 || nc >= N) continue;
            if (grid[nr][nc] == 0) {
                if (!visited[nr][nc]) {
                    visited[nr][nc] = 1;
                    q.push({nr, nc});
                }
            } else if (safeCells.count({nr, nc})) {
                minCost = min(minCost, (long long)grid[nr][nc]);
            }
        }
    }
    if (minCost == LLONG_MAX) return "Impossible";
    long long remaining = Z - minCost;
    if (remaining > 0) return to_string(remaining);
    return "Died " + to_string(minCost - Z + 1);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int M, N;
    if (!(cin >> M >> N)) return 0;
    vector<vector<int>> grid(M, vector<int>(N));
    for (int i = 0; i < M; i++)
        for (int j = 0; j < N; j++) cin >> grid[i][j];
    int sr, sc;
    long long Z;
    cin >> sr >> sc >> Z;
    int S;
    cin >> S;
    set<pair<int, int>> safe;
    for (int i = 0; i < S; i++) {
        int r, c;
        cin >> r >> c;
        safe.insert({r, c});
    }
    cout << solve(M, N, grid, sr, sc, Z, safe) << "\n";
    return 0;
}
