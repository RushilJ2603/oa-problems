#include <bits/stdc++.h>
using namespace std;

// Return a vector of length m: the network strength after each edge is added, in order.
vector<long long> solve(int n, vector<pair<int,int>> &edges) {
    // WRITE YOUR CODE HERE
    return {};
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    cin >> n >> m;
    vector<pair<int,int>> edges(m);
    for (auto &e : edges) cin >> e.first >> e.second;
    auto res = solve(n, edges);
    for (size_t i = 0; i < res.size(); i++)
        cout << res[i] << (i + 1 == res.size() ? '\n' : ' ');
    return 0;
}
