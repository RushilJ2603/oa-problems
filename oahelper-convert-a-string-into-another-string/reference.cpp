#include <bits/stdc++.h>
using namespace std;

int solve(string word1, string word2) {
    int m = (int)word1.size();
    int n = (int)word2.size();
    if (m < n) {
        swap(word1, word2);
        swap(m, n);
    }
    vector<int> dp(n + 1);
    iota(dp.begin(), dp.end(), 0);
    for (int i = 1; i <= m; ++i) {
        int prev = dp[0];
        dp[0] = i;
        for (int j = 1; j <= n; ++j) {
            int temp = dp[j];
            if (word1[i - 1] == word2[j - 1]) {
                dp[j] = prev;
            } else {
                dp[j] = 1 + min({dp[j - 1], dp[j], prev});
            }
            prev = temp;
        }
    }
    return dp[n];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    string word1, word2;
    if (!(cin >> word1 >> word2)) return 0;
    cout << solve(word1, word2) << "\n";
    return 0;
}
