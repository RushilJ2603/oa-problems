#include <bits/stdc++.h>
using namespace std;

long long solve(int n, long long k, long long x, vector<long long>& a) {
    long long total = 0;
    vector<long long> gains;
    gains.reserve(n);
    for (long long v : a) {
        total += v;
        long long gain = (v ^ x) - v;
        if (gain > 0) gains.push_back(gain);
    }
    if (k <= 0 || gains.empty()) return total;
    if (k < (long long)gains.size()) {
        nth_element(gains.begin(), gains.begin() + k, gains.end(), greater<long long>());
        gains.resize((size_t)k);
    }
    for (long long g : gains) total += g;
    return total;
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
