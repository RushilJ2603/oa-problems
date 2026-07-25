#include <bits/stdc++.h>
using namespace std;

long long solve(const string& s, int k) {
    int n = (int)s.size();
    long long ans = 0;
    for (int d = 1; d < n; d++) {
        int m = n - d;
        vector<int> eq(m, 0), left(m, 0), right(m, 0);
        for (int idx = 0; idx < m; idx++) {
            if (s[idx] == s[idx + d]) eq[idx] = 1;
        }
        for (int idx = 0; idx < m; idx++) {
            if (eq[idx] == 0) left[idx] = 0;
            else if (idx == 0) left[idx] = 1;
            else left[idx] = left[idx - 1] + 1;
        }
        for (int idx = m - 1; idx >= 0; idx--) {
            if (eq[idx] == 0) right[idx] = 0;
            else if (idx == m - 1) right[idx] = 1;
            else right[idx] = right[idx + 1] + 1;
        }
        for (int p = k; p < m; p++) {
            bool prefixOk = (k == 0) || (left[p - 1] >= k);
            if (prefixOk && eq[p] == 0) {
                int tail = (p + 1 < m) ? right[p + 1] : 0;
                ans += (long long)tail + 1;
            }
        }
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    string s;
    int k;
    if (!(cin >> s >> k)) return 0;
    cout << solve(s, k) << "\n";
    return 0;
}
