#include <bits/stdc++.h>
using namespace std;

// Min sum of adjacent |differences| after removing one contiguous length-k subarray.
long long minAdjDiff(vector<long long>& a, int k) {
    // WRITE YOUR CODE HERE
    return 0;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, k;
    if (!(cin >> n >> k)) return 0;
    vector<long long> a(n);
    for (auto& x : a) cin >> x;
    cout << minAdjDiff(a, k) << "\n";
    return 0;
}
