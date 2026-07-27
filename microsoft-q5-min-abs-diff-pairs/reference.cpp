#include <bits/stdc++.h>
using namespace std;

// After sorting the distinct values, the minimum absolute difference is always between two
// ADJACENT values (any pair straddling a third value has a strictly smaller adjacent gap).
// So sort+dedup, take the min adjacent gap, then emit every adjacent pair with that gap.
int main() {
    int n;
    if (scanf("%d", &n) != 1) return 0;
    vector<long long> a(n);
    for (auto &x : a) scanf("%lld", &x);
    sort(a.begin(), a.end());
    a.erase(unique(a.begin(), a.end()), a.end());
    if (a.size() < 2) return 0;
    long long best = LLONG_MAX;
    for (size_t i = 1; i < a.size(); i++) best = min(best, a[i] - a[i - 1]);
    string out;
    for (size_t i = 1; i < a.size(); i++)
        if (a[i] - a[i - 1] == best) {
            out += to_string(a[i - 1]);
            out += ' ';
            out += to_string(a[i]);
            out += '\n';
        }
    fputs(out.c_str(), stdout);
    return 0;
}
