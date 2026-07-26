#include <bits/stdc++.h>
using namespace std;

long long solve(int n, vector<vector<long long>>& coins) {
    // O(n) via serpentine prefix + suffix U-turn evaluation
    vector<long long> S0(n), S1(n), KS0(n), KS1(n);
    S0[n - 1] = coins[0][n - 1];
    S1[n - 1] = coins[1][n - 1];
    KS0[n - 1] = (long long)(n - 1) * coins[0][n - 1];
    KS1[n - 1] = (long long)(n - 1) * coins[1][n - 1];
    for (int i = n - 2; i >= 0; --i) {
        S0[i] = S0[i + 1] + coins[0][i];
        S1[i] = S1[i + 1] + coins[1][i];
        KS0[i] = KS0[i + 1] + (long long)i * coins[0][i];
        KS1[i] = KS1[i + 1] + (long long)i * coins[1][i];
    }

    long long max_coins = 0;
    long long serpentine = 0;
    for (int i = 0; i < n; ++i) {
        long long end_t = i + 2LL * n - 1;
        long long u_turn;
        if (i % 2 == 0) {
            u_turn = (KS0[i] + (long long)i * S0[i]) + (end_t * S1[i] - KS1[i]);
            max_coins = max(max_coins, serpentine + u_turn);
            serpentine += (long long)(2 * i) * coins[0][i];
            serpentine += (long long)(2 * i + 1) * coins[1][i];
        } else {
            u_turn = (KS1[i] + (long long)i * S1[i]) + (end_t * S0[i] - KS0[i]);
            max_coins = max(max_coins, serpentine + u_turn);
            serpentine += (long long)(2 * i) * coins[1][i];
            serpentine += (long long)(2 * i + 1) * coins[0][i];
        }
    }
    return max_coins;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    if (!(cin >> n)) return 0;
    vector<vector<long long>> coins(2, vector<long long>(n));
    for (int i = 0; i < n; i++) cin >> coins[0][i];
    for (int i = 0; i < n; i++) cin >> coins[1][i];
    cout << solve(n, coins) << "\n";
    return 0;
}
