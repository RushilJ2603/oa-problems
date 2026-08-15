#include <bits/stdc++.h>
using namespace std;

vector<long long> solve(int N, int S, vector<int>& station, vector<int>& duration, vector<vector<int>>& adj, vector<int>& indegree) {
    // WRITE YOUR CODE HERE
    return vector<long long>(N + 1, 0);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int N, S;
    if (!(cin >> N >> S)) return 0;
    
    vector<int> station(N + 1), duration(N + 1);
    for (int i = 1; i <= N; i++) {
        cin >> station[i] >> duration[i];
    }
    
    int M;
    cin >> M;
    vector<vector<int>> adj(N + 1);
    vector<int> indegree(N + 1, 0);
    for (int i = 0; i < M; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        indegree[v]++;
    }
    
    vector<long long> finish = solve(N, S, station, duration, adj, indegree);
    
    long long makespan = 0;
    for (int i = 1; i <= N; i++) {
        cout << finish[i] << (i == N ? "" : " ");
        makespan = max(makespan, finish[i]);
    }
    cout << "\n" << makespan << "\n";
    return 0;
}
