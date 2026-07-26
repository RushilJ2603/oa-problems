#include <bits/stdc++.h>
using namespace std;

const int MOD = 1000000007;

long long solve(int n, long long k, const vector<pair<int,int>>& edges) {
    // WRITE YOUR CODE HERE
    return 0;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    long long k;
    if (!(cin >> n >> m >> k)) return 0;
    vector<pair<int,int>> edges(m);
    for (int i = 0; i < m; i++) cin >> edges[i].first >> edges[i].second;
    cout << solve(n, k, edges) << "\n";
    return 0;
}
