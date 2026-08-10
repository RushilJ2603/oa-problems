#include <bits/stdc++.h>
using namespace std;

// The bits never interact: flipping bit i of a changes bit i of (a | b) and nothing else. So the
// answer is a sum of independent per-bit costs, and each bit has only two cases:
//
//   c_i == 1 : the OR has to be 1. If either a_i or b_i is already 1 it is free; otherwise turn
//              exactly one of them on -> 1 flip.
//   c_i == 0 : the OR has to be 0, which means BOTH bits must be 0. Every set bit among a_i, b_i
//              has to be cleared -> a_i + b_i flips (so 2 when both are set).
//
// The loop consumes the low bit of all three numbers and shifts, so it stops exactly when there is
// nothing left anywhere. No hard-coded bit count: a 60-bit range and a 64-bit one are the same code.
long long minFlips(unsigned long long a, unsigned long long b, unsigned long long c) {
    long long flips = 0;
    while (a != 0 || b != 0 || c != 0) {
        int ai = (int)(a & 1ULL);
        int bi = (int)(b & 1ULL);
        int ci = (int)(c & 1ULL);
        if (ci == 1) {
            if (ai == 0 && bi == 0) flips += 1;   // the OR needs ONE of them on, not both
        } else {
            flips += ai + bi;                     // the OR needs BOTH off: two flips when both are on
        }
        a >>= 1;
        b >>= 1;
        c >>= 1;
    }
    return flips;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    unsigned long long a, b, c;
    if (!(cin >> a >> b >> c)) return 0;
    cout << minFlips(a, b, c) << "\n";
    return 0;
}
