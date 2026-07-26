#include <bits/stdc++.h>
using namespace std;

long long solve(int n, vector<vector<long long>>& coins) {
    // WRITE YOUR CODE HERE
    return 0;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    if (!(cin >> n)) return 0;
    vector<vector<long long>> coins(2, vector<long long>(n));
    for (int i = 0; i < n; i++) cin >> coins[0][i];
    for (int i = 0; i < n; i++) cin >> coins[1][i];
    cout << solve(n, coins) << "\n";
    return 0;
}
