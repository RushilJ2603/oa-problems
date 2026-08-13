#include <bits/stdc++.h>
using namespace std;

// Z[i] = length of the longest common prefix of t and t[i..]
static vector<int> zFunction(const string &t) {
    const int m = (int)t.size();
    vector<int> z(m, 0);
    if (m) z[0] = m;
    for (int i = 1, l = 0, r = 0; i < m; i++) {
        if (i < r) z[i] = min(r - i, z[i - l]);
        while (i + z[i] < m && t[z[i]] == t[i + z[i]]) z[i]++;
        if (i + z[i] > r) { l = i; r = i + z[i]; }
    }
    return z;
}

// out[x] = length of the longest common prefix of `pattern` and text[x..]
static vector<int> lcpAgainst(const string &pattern, const string &text) {
    string joined = pattern + '\x01' + text;
    vector<int> z = zFunction(joined);
    const int off = (int)pattern.size() + 1;
    vector<int> out((int)text.size() + 1, 0);
    for (int x = 0; x < (int)text.size(); x++) out[x] = min(z[off + x], (int)pattern.size());
    return out;
}

string bestGluedSubstring(const string &s, const string &p, const string &q) {
    const int n = (int)s.size(), np = (int)p.size(), nq = (int)q.size();

    // g[x] = how far s[x..] agrees with q's front. A piece ending at j overlaps q by k exactly when
    // it starts the match k characters earlier, i.e. g[j-k] >= k.
    vector<int> g = lcpAgainst(q, s);

    // The left seam is the mirror image of the right one, so mirror the strings: a SUFFIX of p
    // meeting a PREFIX of s[i..] is a prefix of reverse(p) meeting a suffix of reverse(s).
    string sr(s.rbegin(), s.rend()), pr(p.rbegin(), p.rend());
    vector<int> h = lcpAgainst(pr, sr);
    // s[i..i+k) equals p's last k  <=>  h[n-i-k] >= k.

    // The subtle part. A valid overlap of k does NOT imply k-1 is valid — the two comparisons are
    // between different pairs of substrings — so the answer for a piece of length L is the largest
    // valid k that is AT MOST L, not "the largest valid k, capped at L". Capping is the natural
    // thing to write and it silently overcounts: "cbdcaec" / "ea" / "ca" scores the piece "a" as
    // 1 + 1, because the only overlap on its right seam ("ca", length 2) does not fit inside it.
    //
    // pbest[j][m] = the largest valid right-seam overlap for a piece ending at j, allowed m
    // characters. A running maximum over m, so the "at most" is built in.
    const int mq = min(nq, n);
    vector<int> pbest((size_t)(n + 1) * (mq + 1), 0);
    for (int j = 1; j <= n; j++) {
        const int lim = min(mq, j);
        int *row = &pbest[(size_t)j * (mq + 1)];
        for (int m = 1; m <= lim; m++) row[m] = max(row[m - 1], (g[j - m] >= m) ? m : 0);
    }

    // lcp[i][j] = |LCP(s[i..], s[j..])|, so any two pieces compare in O(1) for the tie-break.
    vector<int> lcp((size_t)(n + 1) * (n + 1), 0);
    for (int i = n - 1; i >= 0; i--) {
        for (int j = n - 1; j >= 0; j--) {
            lcp[(size_t)i * (n + 1) + j] =
                (s[i] == s[j]) ? lcp[(size_t)(i + 1) * (n + 1) + (j + 1)] + 1 : 0;
        }
    }
    auto less_than = [&](int i1, int l1, int i2, int l2) {      // s[i1..i1+l1) < s[i2..i2+l2)
        const int c = lcp[(size_t)i1 * (n + 1) + i2];
        if (c >= min(l1, l2)) return l1 < l2;                   // one is a prefix of the other
        return s[i1 + c] < s[i2 + c];
    };

    int bestScore = -1, bi = 0, bl = 1;
    for (int i = 0; i < n; i++) {
        int pfx = 0;                    // largest valid left-seam overlap that fits in L, so far
        for (int j = i + 1; j <= n; j++) {
            const int L = j - i;
            // Growing the piece by one makes exactly one new overlap length reachable: k = L.
            if (L <= np && h[n - i - L] >= L) pfx = L;
            const int sfx = pbest[(size_t)j * (mq + 1) + min(L, min(mq, j))];
            const int sc = pfx + sfx;
            if (sc > bestScore || (sc == bestScore && less_than(i, L, bi, bl))) {
                bestScore = sc; bi = i; bl = L;
            }
        }
    }
    return s.substr(bi, bl);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    string s, p, q;
    if (!(cin >> s)) return 0;
    cin >> p >> q;
    cout << bestGluedSubstring(s, p, q) << "\n";
    return 0;
}
