#include <bits/stdc++.h>
using namespace std;

// Return the maximum total value of a subset of items with total weight <= W.
long long knapsack(int W, vector<long long>& val, vector<long long>& wt) {
    // WRITE YOUR CODE HERE
    return 0;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int N, W;
    if (!(cin >> N >> W)) return 0;
    vector<long long> val(N), wt(N);
    for (auto& x : val) cin >> x;
    for (auto& x : wt) cin >> x;
    cout << knapsack(W, val, wt) << "\n";
    return 0;
}
