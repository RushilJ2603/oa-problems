#include <bits/stdc++.h>
using namespace std;

bool solve(int n, int m, vector<pair<int,int>>& edges, int a, int b) {
    // WRITE YOUR CODE HERE
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    if (!(cin >> n >> m)) return 0;
    vector<pair<int,int>> edges(m);
    for (int i = 0; i < m; i++) cin >> edges[i].first >> edges[i].second;
    int a, b;
    cin >> a >> b;
    cout << (solve(n, m, edges, a, b) ? "true" : "false") << "\n";
    return 0;
}
