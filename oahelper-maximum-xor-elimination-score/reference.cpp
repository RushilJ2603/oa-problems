#include <bits/stdc++.h>
using namespace std;

long long solve(int n, vector<long long>& a) {
    if (n <= 1) return 0;
    vector<long long> key(n, -1);
    vector<char> used(n, 0);
    key[0] = 0;
    long long total = 0;
    for (int it = 0; it < n; it++) {
        int u = -1;
        for (int v = 0; v < n; v++)
            if (!used[v] && (u == -1 || key[v] > key[u])) u = v;
        used[u] = 1;
        total += key[u];
        for (int v = 0; v < n; v++) {
            if (!used[v]) {
                long long w = a[u] ^ a[v];
                if (w > key[v]) key[v] = w;
            }
        }
    }
    return total;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    if (!(cin >> n)) return 0;
    vector<long long> a(n);
    for (auto& x : a) cin >> x;
    cout << solve(n, a) << "\n";
    return 0;
}
