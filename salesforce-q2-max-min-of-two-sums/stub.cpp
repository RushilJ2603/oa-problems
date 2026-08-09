#include <bits/stdc++.h>
using namespace std;

int maxBalancedValue(int n, int k, const vector<int> &a, const vector<int> &b) {
    // WRITE YOUR CODE HERE
    return 0;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, k;
    if (!(cin >> n >> k)) return 0;
    vector<int> a(n), b(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    for (int i = 0; i < n; i++) cin >> b[i];
    cout << maxBalancedValue(n, k, a, b) << "\n";
    return 0;
}
