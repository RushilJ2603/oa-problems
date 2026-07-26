#include <bits/stdc++.h>
using namespace std;

long long computeMinG(long long sum_d, long long odd_cnt) {
    if (sum_d == 0) return 0;
    long long g1 = (odd_cnt > 0) ? (2 * odd_cnt - 1) : 0;
    long long even_threshold = (2 * sum_d + 2) / 3;
    long long min_even_g2 = (even_threshold % 2 == 0) ? even_threshold : even_threshold + 1;
    long long odd_threshold = (2 * sum_d + 3) / 3;
    long long min_odd_g2 = (odd_threshold % 2 == 1) ? odd_threshold : odd_threshold + 1;
    long long g2 = min(min_even_g2, min_odd_g2);
    return max(g1, g2);
}

long long solve(int n, vector<long long>& layer) {
    long long max_layer = *max_element(layer.begin(), layer.end());
    long long sum_layer = 0;
    for (long long x : layer) sum_layer += x;
    long long ans = LLONG_MAX;
    for (int delta = 0; delta <= 1; delta++) {
        long long T = max_layer + delta;
        long long sum_d = (long long)n * T - sum_layer;
        long long odd_cnt = 0;
        for (long long x : layer)
            if ((T - x) % 2 == 1) odd_cnt++;
        ans = min(ans, computeMinG(sum_d, odd_cnt));
    }
    return ans;
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
