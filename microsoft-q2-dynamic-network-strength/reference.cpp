#include <bits/stdc++.h>
using namespace std;

// DSU with union-by-size + path compression, keeping the max label per component.
// The running sum is maintained INCREMENTALLY: on a real union we subtract the two
// old maxima and add the merged max. This is O((n+m) alpha) — the point of the
// problem is to avoid recomputing the whole sum each second (which is what TLEs).
static int par[200005], mx[200005], sz[200005];

int find(int x) {
    while (par[x] != x) { par[x] = par[par[x]]; x = par[x]; }
    return x;
}

int main() {
    int n, m;
    if (scanf("%d %d", &n, &m) != 2) return 0;
    long long sum = 0;
    for (int i = 1; i <= n; i++) { par[i] = i; mx[i] = i; sz[i] = 1; sum += i; }

    string out;
    out.reserve((size_t)m * 7);
    for (int i = 0; i < m; i++) {
        int u, v; scanf("%d %d", &u, &v);
        int a = find(u), b = find(v);
        if (a != b) {
            sum -= mx[a];
            sum -= mx[b];
            if (sz[a] < sz[b]) swap(a, b);
            par[b] = a;
            sz[a] += sz[b];
            if (mx[b] > mx[a]) mx[a] = mx[b];
            sum += mx[a];
        }
        out += to_string(sum);
        out += (i + 1 < m ? ' ' : '\n');
    }
    fputs(out.c_str(), stdout);
    return 0;
}
