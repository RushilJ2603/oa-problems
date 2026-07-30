#include <bits/stdc++.h>
using namespace std;

// Seat the guests in sorted (demand) order around the circle. Then the gap between two neighbours only
// has to satisfy the LARGER of their two demands, and a sorted cyclic order provably minimises the
// total required empty space. That minimum total gap equals (sum of demands - smallest) + largest, so
// the whole banquet needs n occupied chairs + that many empty ones. Feasible iff m is at least that.
// (n == 1 collapses to "m - 1 >= demand", and n == 0 is always fine — the formula handles both.)
bool solve(long long m, const vector<long long>& d) {
    long long n = (long long)d.size();
    if (n == 0) return true;
    long long S = 0, mn = LLONG_MAX, mx = 0;
    for (long long x : d) {
        S += x;
        mn = min(mn, x);
        mx = max(mx, x);
    }
    long long need = n + (S - mn) + mx;
    return m >= need;
}

int main() {
    long long m, n;
    if (scanf("%lld %lld", &m, &n) != 2) return 0;
    vector<long long> d(n);
    for (auto& x : d) scanf("%lld", &x);
    puts(solve(m, d) ? "YES" : "NO");
    return 0;
}
