#include <bits/stdc++.h>
using namespace std;

const int MOD = 1000000007;

long long solve(int r, int b) {
    long long total = (long long)r + b;
    int h = 0;
    while ((long long)(h + 1) * (h + 2) / 2 <= total) h++;
    if (h == 0) return 0;
    long long S = (long long)h * (h + 1) / 2;
    // DP over smaller color budget
    if (r > b) swap(r, b);
    vector<int> dp(r + 1, 0);
    dp[0] = 1;
    for (int i = 1; i <= h; i++) {
        int max_j = min(r, i * (i + 1) / 2);
        for (int j = max_j; j >= i; j--) {
            dp[j] += dp[j - i];
            if (dp[j] >= MOD) dp[j] -= MOD;
        }
    }
    long long ans = 0;
    int low = max(0LL, S - b);
    int high = min(S, (long long)r);
    for (int k = low; k <= high; k++) {
        ans += dp[k];
        if (ans >= MOD) ans -= MOD;
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int r, b;
    if (!(cin >> r >> b)) return 0;
    cout << solve(r, b) << "\n";
    return 0;
}
