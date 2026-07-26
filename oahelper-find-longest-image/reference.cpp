#include <bits/stdc++.h>
using namespace std;

int solve(int k, vector<vector<int>>& colors) {
    if (colors.empty() || colors[0].empty()) return 0;
    int n = (int)colors.size();
    int m = (int)colors[0].size();
    vector<deque<int>> max_deqs(n), min_deqs(n);
    int L = 0;
    int ans = 0;
    for (int R = 0; R < m; ++R) {
        for (int i = 0; i < n; ++i) {
            while (!max_deqs[i].empty() && colors[i][max_deqs[i].back()] <= colors[i][R])
                max_deqs[i].pop_back();
            max_deqs[i].push_back(R);
            while (!min_deqs[i].empty() && colors[i][min_deqs[i].back()] >= colors[i][R])
                min_deqs[i].pop_back();
            min_deqs[i].push_back(R);
        }
        while (L <= R) {
            bool ok = true;
            for (int i = 0; i < n; ++i) {
                if ((long long)colors[i][max_deqs[i].front()] -
                    (long long)colors[i][min_deqs[i].front()] > k) {
                    ok = false;
                    break;
                }
            }
            if (!ok) {
                for (int i = 0; i < n; ++i) {
                    if (max_deqs[i].front() == L) max_deqs[i].pop_front();
                    if (min_deqs[i].front() == L) min_deqs[i].pop_front();
                }
                ++L;
            } else {
                break;
            }
        }
        ans = max(ans, R - L + 1);
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int k, n, m;
    if (!(cin >> k >> n >> m)) return 0;
    vector<vector<int>> colors(n, vector<int>(m));
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
            cin >> colors[i][j];
    cout << solve(k, colors) << "\n";
    return 0;
}
