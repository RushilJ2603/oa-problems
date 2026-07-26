#include <bits/stdc++.h>
using namespace std;

long long solve(int n, vector<int>& parent, vector<int>& values) {
    // WRITE YOUR CODE HERE
    return 0;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    if (!(cin >> n)) return 0;
    vector<int> parent(n), values(n);
    for (int i = 0; i < n; ++i) cin >> parent[i];
    for (int i = 0; i < n; ++i) cin >> values[i];
    cout << solve(n, parent, values) << "\n";
    return 0;
}
