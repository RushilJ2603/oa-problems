#include <bits/stdc++.h>
using namespace std;

long long solve(int n, vector<long long>& chatLoad, int k, vector<int>& reviewMinutes) {
    const long long MOD = 1000000007LL;
    vector<long long> pre(n + 1, 0);
    for (int i = 0; i < n; ++i) pre[i + 1] = pre[i] + chatLoad[i];
    vector<int> r = reviewMinutes;
    sort(r.begin(), r.end());
    int half = k / 2;
    long long total = 0;
    for (int i = 0; i < half; ++i) total -= pre[r[i]];
    for (int i = half; i < k; ++i) total += pre[r[i] + 1];
    long long ans = total % MOD;
    if (ans < 0) ans += MOD;
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    if (!(cin >> n)) return 0;
    vector<long long> chatLoad(n);
    for (auto& x : chatLoad) cin >> x;
    int k;
    cin >> k;
    vector<int> reviewMinutes(k);
    for (auto& x : reviewMinutes) cin >> x;
    cout << solve(n, chatLoad, k, reviewMinutes) << "\n";
    return 0;
}
