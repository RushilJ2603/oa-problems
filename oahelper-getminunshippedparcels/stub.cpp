#include <bits/stdc++.h>
using namespace std;

int solve(vector<int>& weights, long long max_wt) {
    // WRITE YOUR CODE HERE
    return 0;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    if (!(cin >> n)) return 0;
    vector<int> weights(n);
    for (int i = 0; i < n; i++) cin >> weights[i];
    long long max_wt;
    cin >> max_wt;
    cout << solve(weights, max_wt) << "\n";
    return 0;
}
