#include <bits/stdc++.h>
using namespace std;

vector<long long> solve(int n, vector<long long>& values, string state, int m) {
    // WRITE YOUR CODE HERE
    return vector<long long>(m, 0);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    if (!(cin >> n)) return 0;
    vector<long long> values(n);
    for (int i = 0; i < n; ++i) cin >> values[i];
    string state;
    cin >> state;
    int m;
    cin >> m;
    auto ans = solve(n, values, state, m);
    for (auto x : ans) cout << x << "\n";
    return 0;
}
