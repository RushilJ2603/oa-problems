#include <bits/stdc++.h>
using namespace std;

// Minimum operations (replace a contiguous subarray with its sum) to make X and Y
// identical, or -1 if impossible.
long long minMergeOps(const vector<long long>& X, const vector<long long>& Y) {
    // WRITE YOUR CODE HERE
    return -1;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    if (!(cin >> n)) return 0;
    vector<long long> X(n);
    for (auto& x : X) cin >> x;
    int m;
    cin >> m;
    vector<long long> Y(m);
    for (auto& y : Y) cin >> y;
    cout << minMergeOps(X, Y) << "\n";
    return 0;
}
