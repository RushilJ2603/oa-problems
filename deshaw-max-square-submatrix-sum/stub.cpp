#include <bits/stdc++.h>
using namespace std;

// grid is m x n with non-negative values. Return the largest side length L such that some L x L
// contiguous square submatrix has sum <= k. Return 0 if not even a single cell is <= k.
int maxSquareSide(int m, int n, long long k, vector<vector<long long>>& grid) {
    // WRITE YOUR CODE HERE
    return 0;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int m, n;
    long long k;
    if (!(cin >> m >> n >> k)) return 0;
    vector<vector<long long>> grid(m, vector<long long>(n));
    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++) cin >> grid[i][j];
    cout << maxSquareSide(m, n, k, grid) << "\n";
    return 0;
}
