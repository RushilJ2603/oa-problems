#include <bits/stdc++.h>
using namespace std;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n; if (!(cin >> n)) return 0;
    vector<long long> a(n); for (auto& x : a) cin >> x;
    long long best = 0, mn = LLONG_MAX;
    for (long long p : a) { if (p - mn > best) best = p - mn; if (p < mn) mn = p; }
    cout << best << "\n";
    return 0;
}
