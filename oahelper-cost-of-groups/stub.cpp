#include <bits/stdc++.h>
using namespace std;

long long solve(int n, vector<long long>& a, vector<pair<int, int>>& edges) {
    // WRITE YOUR CODE HERE
    return 0;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    if (!(cin >> T)) return 0;
    while (T--) {
        int n;
        cin >> n;
        vector<long long> a(n);
        for (int i = 0; i < n; i++) cin >> a[i];
        vector<pair<int, int>> edges;
        for (int i = 0; i < n - 1; i++) {
            int u, v;
            cin >> u >> v;
            edges.push_back({u, v});
        }
        cout << solve(n, a, edges) << "\n";
    }
    return 0;
}
