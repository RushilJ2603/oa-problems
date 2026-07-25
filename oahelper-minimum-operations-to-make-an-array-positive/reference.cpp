#include <bits/stdc++.h>
using namespace std;

long long solve(int n, vector<long long>& a) {
    // Any L >= 2 decomposes into 2s and 3s, so it is enough (and necessary)
    // to hit every negative length-2 / length-3 window. Overwriting a cell
    // with a huge value covers every window that contains it → classic
    // minimum points to stab intervals, greedy by right endpoint.
    vector<pair<int, int>> iv;
    for (int i = 0; i + 1 < n; ++i)
        if (a[i] + a[i + 1] < 0) iv.push_back({i + 1, i});
    for (int i = 0; i + 2 < n; ++i)
        if (a[i] + a[i + 1] + a[i + 2] < 0) iv.push_back({i + 2, i});
    sort(iv.begin(), iv.end());
    long long last = -1, cnt = 0;
    for (auto& p : iv) {
        if (last < p.second) {
            last = p.first;
            ++cnt;
        }
    }
    return cnt;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    if (!(cin >> n)) return 0;
    vector<long long> a(n);
    for (int i = 0; i < n; ++i) cin >> a[i];
    cout << solve(n, a) << "\n";
    return 0;
}
