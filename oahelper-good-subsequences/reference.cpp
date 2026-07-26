#include <bits/stdc++.h>
using namespace std;

static const long long MOD = 1000000007LL;

long long power_mod(long long base, long long exp) {
    long long res = 1;
    base %= MOD;
    while (exp > 0) {
        if (exp & 1LL) res = res * base % MOD;
        base = base * base % MOD;
        exp >>= 1;
    }
    return res;
}

long long solve(const string& word) {
    vector<long long> cnt(26, 0);
    for (char ch : word) {
        int idx = ch - 'a';
        if (idx >= 0 && idx < 26) cnt[idx]++;
    }
    vector<long long> counts;
    for (int i = 0; i < 26; ++i)
        if (cnt[i] > 0) counts.push_back(cnt[i]);
    if (counts.empty()) return 0;
    sort(counts.begin(), counts.end(), greater<long long>());
    long long maxf = counts[0];

    vector<long long> fact(maxf + 1), invFact(maxf + 1);
    fact[0] = 1;
    for (long long i = 1; i <= maxf; ++i) fact[i] = fact[i - 1] * (i % MOD) % MOD;
    invFact[maxf] = power_mod(fact[maxf], MOD - 2);
    for (long long i = maxf; i >= 1; --i) invFact[i - 1] = invFact[i] * (i % MOD) % MOD;

    long long ans = 0;
    for (long long k = 1; k <= maxf; ++k) {
        long long prod = 1;
        long long ik = invFact[k];
        for (size_t j = 0; j < counts.size(); ++j) {
            long long f = counts[j];
            if (f < k) break;
            long long comb = fact[f] * ik % MOD * invFact[f - k] % MOD;
            prod = prod * ((1 + comb) % MOD) % MOD;
        }
        ans = (ans + prod - 1 + MOD) % MOD;
    }
    return ans % MOD;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    string word;
    if (!(cin >> word)) {
        cout << 0 << "\n";
        return 0;
    }
    cout << solve(word) << "\n";
    return 0;
}
