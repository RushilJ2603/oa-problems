#include <bits/stdc++.h>
using namespace std;

long long solve(int m, vector<long long>& nums) {
    int full = (1 << m) - 1;
    vector<long long> dp(1 << m, -1);
    dp[0] = 0;
    for (int mask = 0; mask <= full; mask++) {
        if (dp[mask] < 0) continue;
        int used = __builtin_popcount(mask);
        if (used & 1) continue;
        int op = used / 2 + 1;
        for (int i = 0; i < m; i++) {
            if (mask & (1 << i)) continue;
            for (int j = i + 1; j < m; j++) {
                if (mask & (1 << j)) continue;
                int nm = mask | (1 << i) | (1 << j);
                long long val = dp[mask] + (long long)op * std::gcd(nums[i], nums[j]);
                if (val > dp[nm]) dp[nm] = val;
            }
        }
    }
    return dp[full];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int m;
    if (!(cin >> m)) return 0;
    vector<long long> nums(m);
    for (int i = 0; i < m; i++) cin >> nums[i];
    cout << solve(m, nums) << "\n";
    return 0;
}
