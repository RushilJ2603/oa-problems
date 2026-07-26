#include <bits/stdc++.h>
using namespace std;

int solve(int n, int m, vector<vector<int>>& grid) {
    // WRITE YOUR CODE HERE
    return 0;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    if (!(cin >> n >> m)) return 0;
    vector<vector<int>> grid(n, vector<int>(m));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            cin >> grid[i][j];
    cout << solve(n, m, grid) << "\n";
    return 0;
}
