#include <bits/stdc++.h>
using namespace std;

// Return the longest simple path from S to D (most cities); on ties, the
// lexicographically smallest vertex sequence. g is the adjacency matrix.
// Return an empty vector if no path exists.
vector<int> preferredRoute(int n, const vector<vector<int>>& g, int S, int D) {
    vector<int> route;
    // WRITE YOUR CODE HERE
    return route;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    if (!(cin >> n)) return 0;
    vector<vector<int>> g(n, vector<int>(n));
    for (auto& row : g)
        for (auto& x : row) cin >> x;
    int S, D;
    cin >> S >> D;

    vector<int> route = preferredRoute(n, g, S, D);
    for (size_t i = 0; i < route.size(); ++i) cout << route[i] << " \n"[i + 1 == route.size()];
    if (route.empty()) cout << "\n";
    return 0;
}
