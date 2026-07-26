#include <bits/stdc++.h>
using namespace std;

int solve(int k, vector<vector<int>>& colors) {
    // WRITE YOUR CODE HERE
    return 0;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int k, n, m;
    if (!(cin >> k >> n >> m)) return 0;
    vector<vector<int>> colors(n, vector<int>(m));
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
            cin >> colors[i][j];
    cout << solve(k, colors) << "\n";
    return 0;
}
