#include <bits/stdc++.h>
using namespace std;

int solve(int m, int n, long long e, vector<vector<long long>>& grid) {
    // WRITE YOUR CODE HERE
    return 0;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int m, n;
    long long e;
    if (!(cin >> m >> n >> e)) return 0;
    vector<vector<long long>> grid(m, vector<long long>(n));
    for (int i = 0; i < m; ++i)
        for (int j = 0; j < n; ++j)
            cin >> grid[i][j];
    cout << solve(m, n, e, grid) << "\n";
    return 0;
}
