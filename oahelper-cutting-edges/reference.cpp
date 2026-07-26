#include <bits/stdc++.h>
using namespace std;

int solve(const string& s) {
    int n = (int)s.size();
    vector<int> prefix(n + 1, 0);
    for (int i = 0; i < n; i++) {
        prefix[i + 1] = (prefix[i] + (s[i] - '0')) % 3;
    }
    const int NEG = -1000000000;
    vector<int> dp(n + 1, NEG);
    dp[0] = 0;
    int best[3] = {NEG, NEG, NEG};
    if (n > 0 && s[0] != '0') {
        best[prefix[0] % 3] = max(best[prefix[0] % 3], dp[0]);
    }
    for (int i = 1; i <= n; i++) {
        int cur = NEG;
        int r = prefix[i] % 3;
        if (best[r] > NEG) {
            cur = max(cur, best[r] + 1);
        }
        int d = s[i - 1] - '0';
        if (d % 3 == 0 && dp[i - 1] > NEG) {
            cur = max(cur, dp[i - 1] + 1);
        }
        dp[i] = cur;
        if (i < n && s[i] != '0' && dp[i] > NEG) {
            int rr = prefix[i] % 3;
            best[rr] = max(best[rr], dp[i]);
        }
    }
    return max(0, dp[n]);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    string s;
    if (!(cin >> s)) return 0;
    cout << solve(s) << "\n";
    return 0;
}
