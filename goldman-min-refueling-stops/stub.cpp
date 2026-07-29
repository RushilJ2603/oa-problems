#include <bits/stdc++.h>
using namespace std;

// Return the minimum number of refueling stops to travel `target` units starting with
// `startFuel`, using the given stations (pos, fuel); or -1 if unreachable.
int solve(long long target, long long startFuel, vector<pair<long long,long long>> stations) {
    // WRITE YOUR CODE HERE
    return -1;
}

int main() {
    long long target, startFuel;
    if (scanf("%lld %lld", &target, &startFuel) != 2) return 0;
    int n;
    if (scanf("%d", &n) != 1) n = 0;
    vector<pair<long long,long long>> st(n);
    for (auto &p : st) scanf("%lld %lld", &p.first, &p.second);
    printf("%d\n", solve(target, startFuel, st));
    return 0;
}
