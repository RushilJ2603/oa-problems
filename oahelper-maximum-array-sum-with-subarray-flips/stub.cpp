#include <bits/stdc++.h>
using namespace std;

long long solve(int n, long long k, vector<long long>& a) {
    // WRITE YOUR CODE HERE
    return 0;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    long long k;
    if (!(cin >> n >> k)) return 0;
    vector<long long> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    cout << solve(n, k, a) << "\n";
    return 0;
}
