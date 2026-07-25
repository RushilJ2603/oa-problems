#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

// Count of y in [0, x] whose binary contains "101" as subsequence
ll count101(ll x) {
    if (x < 0) return 0;
    int B = 62;
    static ll memo[64][4];
    static bool vis[64][4];
    memset(vis, 0, sizeof(vis));
    function<ll(int, int)> freeCnt = [&](int r, int s) -> ll {
        if (s == 3) return (ll)1 << r;
        if (r == 0) return 0;
        if (vis[r][s]) return memo[r][s];
        vis[r][s] = 1;
        ll res = 0;
        for (int b = 0; b < 2; b++) {
            int ns = s;
            if (s == 0) ns = (b == 1) ? 1 : 0;
            else if (s == 1) ns = (b == 1) ? 1 : 2;
            else if (s == 2) ns = (b == 1) ? 3 : 2;
            res += freeCnt(r - 1, ns);
        }
        return memo[r][s] = res;
    };
    ll res = 0;
    int s = 0;
    for (int i = B; i >= 0; i--) {
        int xb = (x >> i) & 1;
        for (int b = 0; b < xb; b++) {
            int ns = s;
            if (s == 0) ns = (b == 1) ? 1 : 0;
            else if (s == 1) ns = (b == 1) ? 1 : 2;
            else if (s == 2) ns = (b == 1) ? 3 : 2;
            else ns = 3;
            res += freeCnt(i, ns);
        }
        int b = xb;
        if (s == 0) s = (b == 1) ? 1 : 0;
        else if (s == 1) s = (b == 1) ? 1 : 2;
        else if (s == 2) s = (b == 1) ? 3 : 2;
        else s = 3;
    }
    if (s == 3) res += 1;
    return res;
}

ll solve(ll L, ll R, ll K) {
    ll base = count101(L - 1);
    ll total = count101(R) - base;
    if (total < K) return -1;
    ll lo = L, hi = R, ans = -1;
    while (lo <= hi) {
        ll mid = lo + ((hi - lo) >> 1);
        if (count101(mid) - base >= K) {
            ans = mid;
            hi = mid - 1;
        } else {
            lo = mid + 1;
        }
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    ll L, R, K;
    if (!(cin >> L >> R >> K)) return 0;
    cout << solve(L, R, K) << "\n";
    return 0;
}
