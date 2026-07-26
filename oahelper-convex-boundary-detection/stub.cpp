#include <bits/stdc++.h>
using namespace std;

vector<pair<int, int>> solve(int n, vector<pair<int, int>>& points) {
    // WRITE YOUR CODE HERE
    return {};
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    if (!(cin >> n)) return 0;
    vector<pair<int, int>> points(n);
    for (int i = 0; i < n; i++) cin >> points[i].first >> points[i].second;
    auto ans = solve(n, points);
    for (size_t i = 0; i < ans.size(); i++) {
        cout << ans[i].first << ' ' << ans[i].second;
        if (i + 1 < ans.size()) cout << '\n';
    }
    return 0;
}
