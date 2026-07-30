#include <bits/stdc++.h>
using namespace std;

// Launch exactly k distinct campaigns (windows [i,j]); each scores max(a[i..j]) - min(a[i..j]).
// Return the maximum achievable total score. Use a 64-bit type for the answer.
long long solve(int n, long long k, const vector<long long>& a) {
    // WRITE YOUR CODE HERE
    return 0;
}

int main() {
    int n;
    long long k;
    if (scanf("%d %lld", &n, &k) != 2) return 0;
    vector<long long> a(n);
    for (auto& x : a) scanf("%lld", &x);
    printf("%lld\n", solve(n, k, a));
    return 0;
}
