#include <bits/stdc++.h>
using namespace std;

// m chairs in a circle, n guests with the given demands. Each guest needs at least demand[i] empty
// chairs on BOTH sides (clockwise and counter-clockwise) before the next guest. Return true iff all
// guests can be seated.
bool solve(long long m, const vector<long long>& d) {
    // WRITE YOUR CODE HERE
    return false;
}

int main() {
    long long m, n;
    if (scanf("%lld %lld", &m, &n) != 2) return 0;
    vector<long long> d(n);
    for (auto& x : d) scanf("%lld", &x);
    puts(solve(m, d) ? "YES" : "NO");
    return 0;
}
