#include <bits/stdc++.h>
using namespace std;

// For each sensor i, return the minimum increment to its range so it overlaps
// at least one other sensor (all others kept at their original ranges).
// p[i] = position, r[i] = range. See the statement for the exact rule.
vector<long long> minIncrements(int n, const vector<long long>& p, const vector<long long>& r) {
    vector<long long> ans;
    // WRITE YOUR CODE HERE
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    if (!(cin >> n)) return 0;
    vector<long long> p(n), r(n);
    for (auto& x : p) cin >> x;
    for (auto& x : r) cin >> x;

    vector<long long> ans = minIncrements(n, p, r);
    string out;
    for (size_t i = 0; i < ans.size(); ++i) { out += to_string(ans[i]); out += (i + 1 < ans.size() ? ' ' : '\n'); }
    cout << out;
    return 0;
}
