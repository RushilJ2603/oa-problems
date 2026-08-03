#include <bits/stdc++.h>
using namespace std;

long long solve(int n, int m, int k,
                const vector<long long>& X,
                const vector<long long>& Y,
                const vector<long long>& Z) {
    // WRITE YOUR CODE HERE
    return 0;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m, k;
    if (!(cin >> n >> m >> k)) return 0;
    vector<long long> X(n), Y(m), Z(k);
    for (int i = 0; i < n; ++i) cin >> X[i];
    for (int i = 0; i < m; ++i) cin >> Y[i];
    for (int i = 0; i < k; ++i) cin >> Z[i];
    cout << solve(n, m, k, X, Y, Z) << "\n";
    return 0;
}
