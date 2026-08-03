#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
static const ll MOD = 1000000007LL;

struct Mat {
    ll a[2][2];
};

static Mat mul(const Mat &x, const Mat &y) {
    Mat r;
    for (int i = 0; i < 2; ++i)
        for (int j = 0; j < 2; ++j) {
            ll s = 0;
            for (int k = 0; k < 2; ++k) s = (s + x.a[i][k] * y.a[k][j]) % MOD;
            r.a[i][j] = s;
        }
    return r;
}

static Mat matPow(Mat m, ll e) {
    Mat r;
    r.a[0][0] = 1; r.a[0][1] = 0; r.a[1][0] = 0; r.a[1][1] = 1;
    while (e > 0) {
        if (e & 1LL) r = mul(r, m);
        m = mul(m, m);
        e >>= 1;
    }
    return r;
}

long long solve(const string& s, const string& t, long long k) {
    int n = (int)s.size();
    if (n == 1 || (int)t.size() != n) return 0;

    string ss = s + s;
    ll cntZero = 0, cntNonZero = 0;
    for (int p = 0; p < n; ++p) {
        if (ss.compare(p, n, t) == 0) {
            if ((n - p) % n == 0) cntZero++;
            else cntNonZero++;
        }
    }
    if (cntZero == 0 && cntNonZero == 0) return 0;

    Mat m;
    m.a[0][0] = 0;
    m.a[0][1] = (ll)(n - 1) % MOD;
    m.a[1][0] = 1;
    m.a[1][1] = (ll)(n - 2) % MOD;

    Mat mk = matPow(m, k);
    ll A = mk.a[0][0] % MOD;
    ll B = mk.a[1][0] % MOD;
    return ((cntZero % MOD) * A + (cntNonZero % MOD) * B) % MOD;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    string s, t;
    long long k;
    if (!(cin >> s >> t >> k)) return 0;
    cout << solve(s, t, k) << "\n";
    return 0;
}
