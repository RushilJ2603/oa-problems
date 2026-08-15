#include <bits/stdc++.h>
using namespace std;

long long solve(int n, int m, int maxTime, vector<int>& fee, vector<vector<int>>& edges, int src, int dest) {
    // WRITE YOUR CODE HERE
    return 0;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n, m, maxTime;
    if (!(cin >> n >> m >> maxTime)) return 0;
    vector<int> fee(n);
    for (int i = 0; i < n; ++i) {
        cin >> fee[i];
    }
    vector<vector<int>> edges(m, vector<int>(3));
    for (int i = 0; i < m; ++i) {
        cin >> edges[i][0] >> edges[i][1] >> edges[i][2];
    }
    int src, dest;
    cin >> src >> dest;
    cout << solve(n, m, maxTime, fee, edges, src, dest) << "\n";
    return 0;
}
