#include <bits/stdc++.h>
using namespace std;

tuple<vector<int>, long long, long long> solveCampaign(
        int n,
        const vector<pair<int,int>>& edges,
        const vector<pair<int,long long>>& seedCosts,
        const vector<long long>& values,
        long long budget, int d) {
    // WRITE YOUR CODE HERE
    return {{}, 0, 0};
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    if (!(cin >> n)) return 0;
    int m; cin >> m;
    vector<pair<int,int>> edges; edges.reserve(m);
    for (int i = 0; i < m; ++i) { int u, v; cin >> u >> v; edges.push_back({u, v}); }
    int s; cin >> s;
    vector<pair<int,long long>> seedCosts; seedCosts.reserve(s);
    for (int i = 0; i < s; ++i) { int id; long long c; cin >> id >> c; seedCosts.push_back({id, c}); }
    vector<long long> values(n);
    for (int i = 0; i < n; ++i) cin >> values[i];
    long long budget; int d;
    cin >> budget >> d;
    auto res = solveCampaign(n, edges, seedCosts, values, budget, d);
    auto& chosen = get<0>(res);
    long long totalValue = get<1>(res), totalCost = get<2>(res);
    cout << '[';
    for (size_t i = 0; i < chosen.size(); ++i) { if (i) cout << ','; cout << chosen[i]; }
    cout << ']' << '\n' << totalValue << '\n' << totalCost << '\n';
    return 0;
}
