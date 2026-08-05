// Smallest substring whose removal leaves every letter distinct.
//
// The whole problem collapses on one observation: what SURVIVES is a prefix followed by a suffix,
// and each of those must itself be all-distinct. Over 26 letters, an all-distinct string is at most
// 26 characters long — so the prefix has at most 27 possible lengths (0..26) and the suffix has at
// most 27 possible start positions, no matter how long the input is. Everything else is bookkeeping.
//
// For each admissible prefix length i we want the smallest suffix start j >= i whose letters are
// distinct AND disjoint from the prefix; the removed block is s[i..j-1], of length j-i. Lengthening
// the prefix can only push j right, so a single sweep suffices — but with <= 27 x 27 candidates the
// cost is irrelevant either way and the loop is written plainly.
#include <bits/stdc++.h>
using namespace std;

int minRemoval(const string &s) {
    int n = (int)s.size();

    // Longest all-distinct prefix: prefix lengths 0..P are the admissible ones.
    int P = 0, m = 0;
    while (P < n) {
        int b = 1 << (s[P] - 'a');
        if (m & b) break;
        m |= b;
        P++;
    }
    // Smallest q such that s[q..n-1] is all-distinct; suffix starts j >= q are the admissible ones,
    // including j = n (delete everything after the prefix).
    int q = n, sm = 0;
    while (q > 0) {
        int b = 1 << (s[q - 1] - 'a');
        if (sm & b) break;
        sm |= b;
        q--;
    }

    // sufMask[j] = letters of s[j..n-1], for j in [q, n]. Only these are all-distinct.
    vector<int> sufMask(n + 1, 0);
    for (int j = n - 1; j >= q; j--) sufMask[j] = sufMask[j + 1] | (1 << (s[j] - 'a'));

    int best = n;                 // deleting everything always works
    int pre = 0;
    for (int i = 0; i <= P; i++) {
        if (i > 0) pre |= 1 << (s[i - 1] - 'a');
        for (int j = max(i, q); j <= n; j++) {
            if ((pre & sufMask[j]) == 0) { best = min(best, j - i); break; }
        }
    }
    return best;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    string s;
    if (!(cin >> s)) return 0;
    cout << minRemoval(s) << "\n";
    return 0;
}
