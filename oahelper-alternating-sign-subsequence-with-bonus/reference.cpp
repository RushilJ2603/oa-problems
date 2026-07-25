#include <bits/stdc++.h>
using namespace std;

long long solve(int n, long long b, vector<long long>& a) {
    const long long NEG = -(1LL << 62);
    long long dp_pos = NEG, dp_neg = NEG;
    for (long long x : a) {
        if (x > 0) {
            long long cand = x;
            if (dp_neg != NEG) cand = max(cand, dp_neg + x + b);
            dp_pos = max(dp_pos, cand);
        } else if (x < 0) {
            long long cand = x;
            if (dp_pos != NEG) cand = max(cand, dp_pos + x + b);
            dp_neg = max(dp_neg, cand);
        }
    }
    long long ans = 0;
    if (dp_pos != NEG) ans = max(ans, dp_pos);
    if (dp_neg != NEG) ans = max(ans, dp_neg);
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    if (!(cin >> n)) return 0;
    long long b;
    cin >> b;
    vector<long long> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    cout << solve(n, b, a) << "\n";
    return 0;
}
