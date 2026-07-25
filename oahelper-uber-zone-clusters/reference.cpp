#include <bits/stdc++.h>
using namespace std;

struct DSU {
    vector<int> parent, sz;
    DSU(int n) : parent(n), sz(n, 1) {
        iota(parent.begin(), parent.end(), 0);
    }
    int find_set(int v) {
        if (v == parent[v]) return v;
        return parent[v] = find_set(parent[v]);
    }
    void union_sets(int a, int b) {
        a = find_set(a);
        b = find_set(b);
        if (a != b) {
            if (sz[a] < sz[b]) swap(a, b);
            parent[b] = a;
            sz[a] += sz[b];
        }
    }
};

vector<int> solve(int n, vector<int>& signature) {
    if (n == 0) return {};
    int max_val = *max_element(signature.begin(), signature.end());
    int MAXV = max_val + 2;
    vector<int> spf(MAXV);
    iota(spf.begin(), spf.end(), 0);
    for (int i = 2; i * i < MAXV; ++i) {
        if (spf[i] == i) {
            for (int j = i * i; j < MAXV; j += i) {
                if (spf[j] == j) spf[j] = i;
            }
        }
    }
    DSU dsu(n);
    vector<int> last_seen(MAXV, -1);
    for (int i = 0; i < n; ++i) {
        int x = signature[i];
        while (x > 1) {
            int p = spf[x];
            if (last_seen[p] != -1) dsu.union_sets(i, last_seen[p]);
            last_seen[p] = i;
            while (x % p == 0) x /= p;
        }
    }
    vector<int> ans(n);
    for (int i = 0; i < n; ++i) ans[i] = dsu.sz[dsu.find_set(i)];
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    if (!(cin >> n)) return 0;
    vector<int> signature(n);
    for (int i = 0; i < n; i++) cin >> signature[i];
    vector<int> ans = solve(n, signature);
    for (int x : ans) cout << x << "\n";
    return 0;
}
