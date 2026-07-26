#include <bits/stdc++.h>
using namespace std;

long long generations_for_target(const vector<long long>& layer, long long T) {
    long long D = 0, odd = 0;
    for (long long x : layer) {
        long long diff = T - x;
        D += diff;
        if (diff & 1) odd++;
    }
    long long g_odd = odd > 0 ? 2 * odd - 1 : 0;
    long long g_cap;
    long long rem = D % 3;
    if (rem == 0) g_cap = 2 * (D / 3);
    else if (rem == 1) g_cap = 2 * (D / 3) + 1;
    else g_cap = 2 * (D / 3) + 2;
    return max(g_odd, g_cap);
}

long long solve(int n, vector<long long>& layer) {
    if (n <= 1) return 0;
    long long mx = layer[0];
    for (int i = 1; i < n; i++) mx = max(mx, layer[i]);
    bool all_eq = true;
    for (int i = 0; i < n; i++)
        if (layer[i] != mx) {
            all_eq = false;
            break;
        }
    if (all_eq) return 0;
    return min(generations_for_target(layer, mx),
               generations_for_target(layer, mx + 1));
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    if (!(cin >> n)) return 0;
    vector<long long> layer(n);
    for (int i = 0; i < n; i++) cin >> layer[i];
    cout << solve(n, layer) << "\n";
    return 0;
}
