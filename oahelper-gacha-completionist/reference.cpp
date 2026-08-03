#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const ll MOD = 998244353LL;

long long solve(int n, vector<int>& w) {
    int W = 0;
    for (int x : w) W += x;
    vector<ll> g(W + 1, 0);
    g[0] = 1;
    int deg = 0;
    for (int i = 0; i < n; i++) {
        int wi = w[i], nd = deg + wi;
        for (int s = nd; s >= wi; s--) {
            g[s] -= g[s - wi];
            if (g[s] < 0) g[s] += MOD;
        }
        deg = nd;
    }
    vector<ll> inv(W + 2, 0);
    if (W >= 1) inv[1] = 1;
    for (int i = 2; i <= W; i++)
        inv[i] = (MOD - (MOD / i) * inv[MOD % i] % MOD) % MOD;
    ll tot = 0;
    for (int s = 1; s <= W; s++)
        if (g[s]) tot = (tot + g[s] % MOD * inv[s]) % MOD;
    return ((-(ll)W) % MOD + MOD) % MOD * tot % MOD;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    if (!(cin >> n)) return 0;
    vector<int> w(n);
    for (auto& x : w) cin >> x;
    cout << solve(n, w) << "\n";
    return 0;
}
