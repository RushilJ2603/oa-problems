#include <bits/stdc++.h>
using namespace std;

long long solve(int n, vector<long long>& a) {
    if (n <= 1) return 0;
    sort(a.begin(), a.end());
    if (n == 2) return a[1] - a[0];
    long long max_diff = 0;
    for (int i = 2; i < n; ++i)
        max_diff = max(max_diff, a[i] - a[i - 2]);
    return max_diff;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    if (!(cin >> n)) return 0;
    vector<long long> a(n);
    for (auto& x : a) cin >> x;
    cout << solve(n, a) << "\n";
    return 0;
}
