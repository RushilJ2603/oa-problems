// For every query node u: how many vertices v on the path from u to the root have the property
// that the letters on the path u..v can be rearranged into a palindrome?
//
// Two ideas.
//
// 1. A multiset of letters can be rearranged into a palindrome iff at most one letter occurs an odd
//    number of times. Only the parity of each of the 26 counts matters, so a path is described by a
//    26-bit mask and the test is popcount(mask) <= 1.
// 2. Let pre(x) be the XOR of the letter-bits from the root down to x, and pre(root's parent) = 0.
//    The path u..v then has mask pre(u) ^ pre(parent(v)). So for a fixed u we must count how many
//    of the prefix masks hanging above u — that is pre(parent(v)) for v on the path, which is
//    exactly {0} U {pre(x) : x a proper ancestor of u} — differ from pre(u) in at most one bit.
//
// That is 27 lookups (equal, or equal-after-flipping-one-of-26-bits) into a counter of the masks
// currently on the root path. One DFS answers EVERY node, so q queries are q array reads afterwards
// — the per-query walk that the naive solution does is what makes it quadratic.
//
// The counter cannot be a flat array: 2^26 ints is 268 MB. It is a small open-addressing table
// instead, sized past the at-most-n distinct masks that are ever inserted. Keys are never deleted,
// only decremented back to zero, which keeps probing correct without tombstones.
//
// The DFS is explicit rather than recursive: a path graph of 2*10^5 nodes would blow the stack.
#include <bits/stdc++.h>
using namespace std;

static const int HB = 20;                       // 2^20 slots >> 2*10^5 keys, so probes stay short
static const int HMASK = (1 << HB) - 1;
static int hkey[1 << HB];
static int hval[1 << HB];

static inline int slot(int k) {
    unsigned h = (unsigned)k * 2654435761u >> (32 - HB);
    while (hkey[h] != -1 && hkey[h] != k) h = (h + 1) & HMASK;
    return (int)h;
}
static inline int getCount(int k) {
    int h = slot(k);
    return hkey[h] == -1 ? 0 : hval[h];
}
static inline void addCount(int k, int d) {
    int h = slot(k);
    hkey[h] = k;
    hval[h] += d;
}

// Answers for every node, computed in one traversal. Queries index into this.
vector<int> palindromicAncestorCounts(int n, const vector<int> &from, const vector<int> &to,
                                      const string &letters) {
    // Adjacency is UNDIRECTED: the input pairs are edges, and the tree is rooted at 0 by the
    // problem, not by the order the endpoints happen to be listed in.
    vector<int> head(n, -1), nxt(2 * (n > 0 ? n : 1)), dest(2 * (n > 0 ? n : 1));
    int ec = 0;
    for (size_t i = 0; i < from.size(); i++) {
        int a = from[i], b = to[i];
        dest[ec] = b; nxt[ec] = head[a]; head[a] = ec++;
        dest[ec] = a; nxt[ec] = head[b]; head[b] = ec++;
    }

    memset(hkey, -1, sizeof(hkey));
    vector<int> ans(n, 0), pre(n, 0), parent(n, -1), it(n), order;
    addCount(0, 1);                              // pre(parent of root) = 0

    vector<int> stk;
    stk.reserve(n);
    parent[0] = -1;
    pre[0] = 1 << (letters[0] - 'a');
    // Entering a node: answer it against the masks above it, then put its own mask in play.
    auto enter = [&](int u) {
        int p = pre[u];
        int c = getCount(p);
        for (int b = 0; b < 26; b++) c += getCount(p ^ (1 << b));
        ans[u] = c;
        addCount(p, 1);
        it[u] = head[u];
    };
    enter(0);
    stk.push_back(0);
    while (!stk.empty()) {
        int u = stk.back();
        int e = it[u];
        if (e == -1) {                           // done with u: take its mask back off the path
            addCount(pre[u], -1);
            stk.pop_back();
            continue;
        }
        it[u] = nxt[e];
        int v = dest[e];
        if (v == parent[u]) continue;
        parent[v] = u;
        pre[v] = pre[u] ^ (1 << (letters[v] - 'a'));
        enter(v);
        stk.push_back(v);
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    if (!(cin >> n)) return 0;
    vector<int> from(n > 0 ? n - 1 : 0), to(n > 0 ? n - 1 : 0);
    for (int i = 0; i < n - 1; i++) cin >> from[i];
    for (int i = 0; i < n - 1; i++) cin >> to[i];
    string letters;
    cin >> letters;
    vector<int> ans = palindromicAncestorCounts(n, from, to, letters);
    int q;
    cin >> q;
    string out;
    for (int i = 0; i < q; i++) {
        int u;
        cin >> u;
        out += to_string(ans[u]);
        out += '\n';
    }
    cout << out;
    return 0;
}
