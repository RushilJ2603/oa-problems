#include <bits/stdc++.h>
using namespace std;

int solve(vector<string>& history) {
    int n = (int)history.size();
    if (n == 0) return 0;
    int m = (int)history[0].size();
    vector<string> rows = history;
    for (auto& s : rows) sort(s.begin(), s.end());
    int total = 0;
    for (int j = 0; j < m; ++j) {
        int mx = 0;
        for (int i = 0; i < n; ++i) {
            mx = max(mx, rows[i][j] - '0');
        }
        total += mx;
    }
    return total;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    if (!(cin >> n)) return 0;
    vector<string> history(n);
    for (int i = 0; i < n; ++i) cin >> history[i];
    cout << solve(history) << "\n";
    return 0;
}
