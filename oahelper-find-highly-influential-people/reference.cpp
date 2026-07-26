#include <bits/stdc++.h>
using namespace std;

vector<int> solve(int n, vector<vector<int>>& arr) {
    vector<int> deg(n, 0);
    int max_deg = -1;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (arr[i][j] == 1) deg[i]++;
        }
        max_deg = max(max_deg, deg[i]);
    }
    vector<int> candidates;
    for (int i = 0; i < n; ++i)
        if (deg[i] == max_deg) candidates.push_back(i);

    vector<int> result;
    int max_score = -1;
    for (int i : candidates) {
        int score = 0;
        for (int j = 0; j < n; ++j)
            if (arr[i][j] == 1) score += deg[j];
        if (score > max_score) {
            max_score = score;
            result.clear();
            result.push_back(i);
        } else if (score == max_score) {
            result.push_back(i);
        }
    }
    return result;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    if (!(cin >> n)) return 0;
    vector<vector<int>> arr(n, vector<int>(n));
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            cin >> arr[i][j];
    vector<int> ans = solve(n, arr);
    for (size_t i = 0; i < ans.size(); ++i) {
        if (i) cout << ' ';
        cout << ans[i];
    }
    cout << "\n";
    return 0;
}
