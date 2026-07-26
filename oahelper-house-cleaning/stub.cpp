#include <bits/stdc++.h>
using namespace std;

int solve(int n, vector<pair<int, int>>& houses) {
    // WRITE YOUR CODE HERE
    return 0;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    if (!(cin >> n)) return 0;
    vector<pair<int, int>> houses(n);
    for (int i = 0; i < n; i++) cin >> houses[i].first >> houses[i].second;
    cout << solve(n, houses) << "\n";
    return 0;
}
