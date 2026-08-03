#include <bits/stdc++.h>
using namespace std;

long long solve(int m, int n, vector<vector<long long>>& grid) {
    // WRITE YOUR CODE HERE
    return 0;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int m, n;
    if (!(cin >> m >> n)) return 0;
    vector<vector<long long>> grid(m, vector<long long>(n));
    for (int i = 0; i < m; ++i)
        for (int j = 0; j < n; ++j)
            cin >> grid[i][j];
    cout << solve(m, n, grid) << "\n";
    return 0;
}
