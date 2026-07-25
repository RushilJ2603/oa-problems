#include <bits/stdc++.h>
using namespace std;

vector<pair<int,int>> solve(int N, long long W, int K,
                            vector<long long>& t, vector<int>& u) {
    // WRITE YOUR CODE HERE
    return vector<pair<int,int>>(N, {0, -1});
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int N, K;
    long long W;
    if (!(cin >> N >> W >> K)) return 0;
    vector<long long> t(N);
    vector<int> u(N);
    for (int i = 0; i < N; i++) cin >> t[i] >> u[i];
    auto res = solve(N, W, K, t, u);
    for (auto &p : res) cout << p.first << " " << p.second << "\n";
    return 0;
}
