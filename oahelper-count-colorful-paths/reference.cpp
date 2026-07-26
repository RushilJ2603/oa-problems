#include <bits/stdc++.h>
using namespace std;

int n, m;
vector<vector<int>> grid;

int dfs(int r, int c, vector<char>& vis) {
    int color = grid[r][c];
    if (vis[color]) return 0;
    if (r == n - 1 && c == m - 1) return 1;
    vis[color] = 1;
    int paths = 0;
    if (r + 1 < n) paths += dfs(r + 1, c, vis);
    if (c + 1 < m) paths += dfs(r, c + 1, vis);
    vis[color] = 0;
    return paths;
}

int solve(int N, int M, vector<vector<int>>& g) {
    n = N;
    m = M;
    grid = g;
    vector<char> vis(101, 0);
    return dfs(0, 0, vis);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int N, M;
    if (!(cin >> N >> M)) return 0;
    vector<vector<int>> g(N, vector<int>(M));
    for (int i = 0; i < N; i++)
        for (int j = 0; j < M; j++)
            cin >> g[i][j];
    cout << solve(N, M, g) << "\n";
    return 0;
}
