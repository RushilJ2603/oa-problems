#include <bits/stdc++.h>
using namespace std;

struct Candidate {
    int id;
    long long cost;
    vector<int> reach;
};

tuple<vector<int>, long long, long long> solveCampaign(
        int n,
        const vector<pair<int,int>>& edges,
        const vector<pair<int,long long>>& seedCosts,
        const vector<long long>& values,
        long long budget, int d) {
    vector<vector<int>> g(n + 1);
    for (auto& e : edges) {
        int u = e.first, v = e.second;
        if (u >= 1 && u <= n && v >= 1 && v <= n) {
            g[u].push_back(v);
            g[v].push_back(u);
        }
    }

    vector<Candidate> cands;
    cands.reserve(seedCosts.size());
    for (auto& sc : seedCosts) {
        int id = sc.first; long long cost = sc.second;
        if (id < 1 || id > n) continue;
        vector<int> reach;
        vector<int> dist(n + 1, -1);
        queue<int> q;
        dist[id] = 0; q.push(id);
        while (!q.empty()) {
            int u = q.front(); q.pop();
            reach.push_back(u);
            if (dist[u] == d) continue;
            for (int v : g[u]) {
                if (dist[v] == -1) { dist[v] = dist[u] + 1; q.push(v); }
            }
        }
        cands.push_back({id, cost, std::move(reach)});
    }

    vector<char> reached(n + 1, 0);
    vector<char> chosenFlag(n + 1, 0);
    vector<int> chosen;
    long long totalCost = 0, totalValue = 0;

    while (true) {
        int bestIdx = -1;
        long long bGain = -1, bCost = 0; int bId = 0;
        for (int i = 0; i < (int)cands.size(); ++i) {
            const auto& c = cands[i];
            if (chosenFlag[c.id]) continue;
            if (totalCost + c.cost > budget) continue;
            long long gain = 0;
            for (int u : c.reach) if (!reached[u]) gain += values[u - 1];
            if (gain <= 0) continue;
            bool better = false;
            if (bestIdx == -1) better = true;
            else {
                long long lhs = gain * bCost, rhs = bGain * c.cost;
                if (lhs > rhs) better = true;
                else if (lhs == rhs) {
                    if (gain > bGain) better = true;
                    else if (gain == bGain) {
                        if (c.cost < bCost) better = true;
                        else if (c.cost == bCost && c.id < bId) better = true;
                    }
                }
            }
            if (better) { bestIdx = i; bGain = gain; bCost = c.cost; bId = c.id; }
        }
        if (bestIdx == -1) break;
        const auto& c = cands[bestIdx];
        chosenFlag[c.id] = 1;
        chosen.push_back(c.id);
        totalCost += c.cost;
        for (int u : c.reach) if (!reached[u]) { reached[u] = 1; totalValue += values[u - 1]; }
    }
    return {chosen, totalValue, totalCost};
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
