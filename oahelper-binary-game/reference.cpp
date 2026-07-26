#include <bits/stdc++.h>
using namespace std;

int solve(int min_length, int max_length, int one_group, int zero_group) {
    const int MOD = 1000000007;
    vector<int> dp(max_length + 1, 0);
    dp[0] = 1;
    for (int i = 1; i <= max_length; ++i) {
        if (i >= one_group) {
            dp[i] += dp[i - one_group];
            if (dp[i] >= MOD) dp[i] -= MOD;
        }
        if (i >= zero_group) {
            dp[i] += dp[i - zero_group];
            if (dp[i] >= MOD) dp[i] -= MOD;
        }
    }
    int total = 0;
    for (int i = min_length; i <= max_length; ++i) {
        total += dp[i];
        if (total >= MOD) total -= MOD;
    }
    return total;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int min_length, max_length, one_group, zero_group;
    if (!(cin >> min_length >> max_length >> one_group >> zero_group)) return 0;
    cout << solve(min_length, max_length, one_group, zero_group) << "\n";
    return 0;
}
