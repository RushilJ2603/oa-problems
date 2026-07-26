#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const ll MOD = 1000000007LL;

ll modpow(ll base, ll exp) {
    ll res = 1 % MOD;
    base %= MOD;
    while (exp > 0) {
        if (exp & 1) res = res * base % MOD;
        base = base * base % MOD;
        exp >>= 1;
    }
    return res;
}

long long solve(int n, vector<long long>& A, vector<long long>& B) {
    sort(A.rbegin(), A.rend());
    sort(B.begin(), B.end());
    ll val = 0;
    for (int i = 0; i < n; i++) {
        ll p = modpow(2, A[i]);
        val = (val * p % MOD + p - 1 + MOD) % MOD;
        val = val * modpow(2, B[i]) % MOD;
    }
    return val % MOD;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    if (!(cin >> n)) return 0;
    vector<long long> A(n), B(n);
    for (int i = 0; i < n; i++) cin >> A[i];
    for (int i = 0; i < n; i++) cin >> B[i];
    cout << solve(n, A, B) << "\n";
    return 0;
}
