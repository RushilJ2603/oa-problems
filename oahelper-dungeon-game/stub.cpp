#include <bits/stdc++.h>
using namespace std;

int solve(int m, int n, vector<vector<int>>& dungeon) {
    // WRITE YOUR CODE HERE
    return 0;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int m, n;
    if (!(cin >> m >> n)) return 0;
    vector<vector<int>> dungeon(m, vector<int>(n));
    for (int i = 0; i < m; ++i)
        for (int j = 0; j < n; ++j)
            cin >> dungeon[i][j];
    cout << solve(m, n, dungeon) << "\n";
    return 0;
}
