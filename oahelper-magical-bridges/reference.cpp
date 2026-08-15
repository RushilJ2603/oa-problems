#include <bits/stdc++.h>
using namespace std;

long long solve(int N, int M, int K, vector<vector<int>>& roads, vector<vector<int>>& bridges) {
    vector<vector<pair<int, long long>>> adj(N + 1);
    for (const auto& road : roads) {
        adj[road[0]].push_back({road[1], road[2]});
        adj[road[1]].push_back({road[0], road[2]});
    }
    for (const auto& bridge : bridges) {
        adj[bridge[0]].push_back({bridge[1], 0});
        adj[bridge[1]].push_back({bridge[0], 0});
    }
    
    vector<long long> dist(N + 1, -1);
    priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>> pq;
    pq.push({0, 1});
    
    while (!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();
        
        if (dist[u] != -1) continue;
        dist[u] = d;
        if (u == N) return d;
        
        for (const auto& edge : adj[u]) {
            if (dist[edge.first] == -1) {
                pq.push({d + edge.second, edge.first});
            }
        }
    }
    
    return dist[N];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int N, M, K;
    if (!(cin >> N >> M >> K)) return 0;
    vector<vector<int>> roads(M, vector<int>(3));
    for (int i = 0; i < M; ++i) {
        cin >> roads[i][0] >> roads[i][1] >> roads[i][2];
    }
    vector<vector<int>> bridges(K, vector<int>(2));
    for (int i = 0; i < K; ++i) {
        cin >> bridges[i][0] >> bridges[i][1];
    }
    cout << solve(N, M, K, roads, bridges) << "\n";
    return 0;
}
