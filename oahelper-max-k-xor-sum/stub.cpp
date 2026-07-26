#include <bits/stdc++.h>
using namespace std;

long long solve(int n, long long k, long long x, vector<long long>& a) {
    // WRITE YOUR CODE HERE
    return 0;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    if (!(cin >> n)) return 0;
    long long k, x;
    cin >> k >> x;
    vector<long long> a(n);
    for (int i = 0; i < n; ++i) cin >> a[i];
    cout << solve(n, k, x, a) << "\n";
    return 0;
}
