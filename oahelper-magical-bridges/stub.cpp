#include <bits/stdc++.h>
using namespace std;

long long solve(int N, int M, int K, vector<vector<int>>& roads, vector<vector<int>>& bridges) {
    // WRITE YOUR CODE HERE
    return 0;
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
