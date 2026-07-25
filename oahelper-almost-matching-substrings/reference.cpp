#include <bits/stdc++.h>
using namespace std;

long long solve(const string& s, int k) {
    const int n = (int)s.size();
    long long total = 0;
    vector<int> bad;
    bad.reserve(n);
    for (int d = 1; d < n; ++d) {
        const int m = n - d;
        if (m <= k) break;
        bad.clear();
        for (int x = 0; x < m; ++x)
            if (s[x] != s[x + d]) bad.push_back(x);
        if (bad.empty()) continue;
        long long prv = -1;
        for (size_t t = 0; t < bad.size(); ++t) {
            const long long a = bad[t];
            const long long nxt = (t + 1 < bad.size()) ? bad[t + 1] : m;
            if (a >= k && a - prv - 1 >= k) total += nxt - a;
            prv = a;
        }
    }
    return 2 * total;
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
