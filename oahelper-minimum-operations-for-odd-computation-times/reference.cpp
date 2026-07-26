#include <bits/stdc++.h>
using namespace std;

int solve(int n, vector<int>& a) {
    unordered_map<int, int> max_k;
    max_k.reserve(n * 2);
    for (int x : a) {
        int k = __builtin_ctz(x);
        int base = x >> k;
        auto it = max_k.find(base);
        if (it == max_k.end() || it->second < k) max_k[base] = k;
    }
    int ops = 0;
    for (auto& p : max_k) ops += p.second;
    return ops;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    if (!(cin >> n)) return 0;
    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    cout << solve(n, a) << "\n";
    return 0;
}
