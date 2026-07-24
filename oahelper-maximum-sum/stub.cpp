#include <bits/stdc++.h>
using namespace std;

// Maximum array sum after performing exactly k sign flips.
long long maximizeSum(vector<long long>& arr, long long k) {
    // WRITE YOUR CODE HERE
    return 0;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    long long k;
    if (!(cin >> n >> k)) return 0;
    vector<long long> arr(n);
    for (auto& x : arr) cin >> x;
    cout << maximizeSum(arr, k) << "\n";
    return 0;
}
