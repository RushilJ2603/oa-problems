#include <bits/stdc++.h>
using namespace std;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n; if (!(cin >> n)) return 0;
    vector<long long> s(n); for (auto& x : s) cin >> x;
    int m; cin >> m;
    vector<long long> c(m); for (auto& x : c) cin >> x;
    sort(s.begin(), s.end());
    sort(c.begin(), c.end());
    int i = 0, j = 0, cnt = 0;
    while (i < n && j < m) {
        if (c[j] >= s[i]) { ++cnt; ++i; ++j; }
        else ++j;
    }
    cout << cnt << "\n";
    return 0;
}
