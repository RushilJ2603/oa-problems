#include <bits/stdc++.h>
using namespace std;

long long solve(int n, int k, vector<vector<long long>>& cost) {
    // WRITE YOUR CODE HERE
    return 0;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, k;
    if (!(cin >> n >> k)) return 0;
    vector<vector<long long>> cost(n, vector<long long>(n));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            cin >> cost[i][j];
    cout << solve(n, k, cost) << "\n";
    return 0;
}
