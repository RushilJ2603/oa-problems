#include <bits/stdc++.h>
using namespace std;

int solve(int N, vector<int>& A, vector<int>& B) {
    int M = (int)A.size();
    vector<vector<int>> adj(N);
    vector<int> degree(N, 0);
    for (int i = 0; i < M; i++) {
        int u = A[i], v = B[i];
        adj[u].push_back(v);
        adj[v].push_back(u);
        degree[u]++;
        degree[v]++;
    }
    queue<int> q;
    vector<char> removed(N, 0);
    for (int i = 0; i < N; i++) {
        if (degree[i] <= 1) q.push(i);
    }
    int seconds = 0;
    while (!q.empty()) {
        seconds++;
        int sz = (int)q.size();
        for (int i = 0; i < sz; i++) {
            int u = q.front();
            q.pop();
            if (removed[u]) continue;
            removed[u] = 1;
            for (int v : adj[u]) {
                if (removed[v]) continue;
                degree[v]--;
                if (degree[v] == 1) q.push(v);
            }
        }
    }
    return seconds;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int N, M;
    if (!(cin >> N >> M)) return 0;
    vector<int> A(M), B(M);
    for (int i = 0; i < M; i++) cin >> A[i];
    for (int i = 0; i < M; i++) cin >> B[i];
    cout << solve(N, A, B) << "\n";
    return 0;
}
