#include <bits/stdc++.h>
using namespace std;

long long solve(int n, vector<long long>& a) {
    if (n == 0) return 0;
    long long dpPrevPrev = 0;
    long long dpPrev = a[0];
    for (int i = 2; i <= n; i++) {
        long long noSwap = dpPrev + a[i - 1] * (long long)i;
        long long doSwap = dpPrevPrev + a[i - 2] * (long long)i + a[i - 1] * (long long)(i - 1);
        long long cur = noSwap > doSwap ? noSwap : doSwap;
        dpPrevPrev = dpPrev;
        dpPrev = cur;
    }
    return dpPrev;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    if (!(cin >> n)) return 0;
    vector<long long> a(n);
    for (auto& x : a) cin >> x;
    cout << solve(n, a) << "\n";
    return 0;
}
