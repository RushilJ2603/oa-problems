#include <bits/stdc++.h>
using namespace std;

// Two sums have to be traded off against each other, so one of them goes into the DP STATE and the
// other becomes the value being maximised:
//     dp[j][s] = the largest totB reachable using exactly j chosen indices whose totA is exactly s
// Then the answer is max over s of min(s, dp[k][s]).  a[i] <= 100 and n <= 50 cap s at 5000, which
// is what makes carrying totA in the state affordable.
int maxBalancedValue(int n, int k, const vector<int> &a, const vector<int> &b) {
    int S = 0;
    for (int i = 0; i < n; i++) S += a[i];

    const int NEG = -1;
    vector<vector<int>> dp(k + 1, vector<int>(S + 1, NEG));
    dp[0][0] = 0;

    for (int i = 0; i < n; i++) {
        int ai = a[i], bi = b[i];
        // j descending so each index is used at most once (the 0/1-knapsack sweep).
        for (int j = min(i, k - 1); j >= 0; j--) {
            const vector<int> &cur = dp[j];
            vector<int> &nxt = dp[j + 1];
            for (int s = S - ai; s >= 0; s--) {
                if (cur[s] < 0) continue;
                int cand = cur[s] + bi;
                if (cand > nxt[s + ai]) nxt[s + ai] = cand;
            }
        }
    }

    int best = 0;
    for (int s = 0; s <= S; s++) {
        if (dp[k][s] < 0) continue;
        best = max(best, min(s, dp[k][s]));
    }
    return best;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, k;
    if (!(cin >> n >> k)) return 0;
    vector<int> a(n), b(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    for (int i = 0; i < n; i++) cin >> b[i];
    cout << maxBalancedValue(n, k, a, b) << "\n";
    return 0;
}
