#include <bits/stdc++.h>
using namespace std;

int solve(int m, int n, vector<vector<long long>>& matrix) {
    // WRITE YOUR CODE HERE
    return 0;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int m, n;
    if (!(cin >> m)) return 0;
    if (!(cin >> n)) return 0;
    vector<vector<long long>> matrix(m, vector<long long>(n));
    for (int i = 0; i < m; ++i)
        for (int j = 0; j < n; ++j)
            cin >> matrix[i][j];
    cout << solve(m, n, matrix) << "\n";
    return 0;
}
