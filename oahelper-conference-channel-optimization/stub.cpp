#include <bits/stdc++.h>
using namespace std;

long long solve(int n, int m, vector<int>& u, vector<int>& v, vector<long long>& w) {
    // WRITE YOUR CODE HERE
    return 0;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    if (!(cin >> n >> m)) return 0;
    vector<int> u(m), v(m);
    vector<long long> w(m);
    for (int i = 0; i < m; i++) cin >> u[i] >> v[i] >> w[i];
    cout << solve(n, m, u, v, w) << "\n";
    return 0;
}
