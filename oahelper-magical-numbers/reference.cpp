#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

// A magical number is a power of two OR a factorial. Powers of two alone already represent every n
// (that is just binary), and using popcount(n) of them is optimal for the "powers of two only" part.
// The only factorials that add anything are the ones that are NOT powers of two — 6, 24, 120, 720,
// 5040, 40320, 362880, 3628800, 39916800, 479001600 — ten of them below 10^9. So enumerate which of
// those ten are used (2^10 subsets) and fill the remainder with distinct powers of two.
static vector<ll> extraFactorials() {
    vector<ll> f;
    ll v = 1;
    for (int a = 2; ; a++) {
        v *= a;                       // 2!, 3!, 4!, ...
        if (v > 1000000000LL) break;
        if (v & (v - 1)) f.push_back(v);   // skip 2 (a power of two, already covered by popcount)
    }
    return f;
}

int minMagicalTerms(ll n, const vector<ll> &fact) {
    int m = (int)fact.size();
    int best = INT_MAX;
    for (int mask = 0; mask < (1 << m); mask++) {
        ll used = 0;
        int cnt = 0;
        for (int i = 0; i < m; i++) {
            if (mask >> i & 1) {
                used += fact[i];
                cnt++;
                if (used > n) break;
            }
        }
        if (used > n) continue;
        ll rem = n - used;
        int total = cnt + __builtin_popcountll((unsigned long long)rem);
        if (total < best) best = total;
    }
    return best == INT_MAX ? -1 : best;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    vector<ll> fact = extraFactorials();
    int t;
    if (!(cin >> t)) return 0;
    while (t--) {
        ll n;
        cin >> n;
        cout << minMagicalTerms(n, fact) << "\n";
    }
    return 0;
}
