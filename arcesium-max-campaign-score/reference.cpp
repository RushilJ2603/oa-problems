#include <bits/stdc++.h>
using namespace std;

// Each campaign is a distinct window [i,j] scoring max(a[i..j]) - min(a[i..j]). We may reuse no window
// twice, so the best k campaigns are simply the k highest window-scores. Enumerate every window's
// score in O(n^2) (sweeping j keeps a running max/min), sort descending, and sum the top k.
long long solve(int n, long long k, const vector<long long>& a) {
    vector<long long> scores;
    scores.reserve((size_t)n * (n + 1) / 2);
    for (int i = 0; i < n; i++) {
        long long mx = a[i], mn = a[i];
        for (int j = i; j < n; j++) {
            mx = max(mx, a[j]);
            mn = min(mn, a[j]);
            scores.push_back(mx - mn);
        }
    }
    sort(scores.begin(), scores.end(), greater<long long>());
    long long lim = min(k, (long long)scores.size());
    long long total = 0;
    for (long long t = 0; t < lim; t++) total += scores[t];
    return total;
}

int main() {
    int n;
    long long k;
    if (scanf("%d %lld", &n, &k) != 2) return 0;
    vector<long long> a(n);
    for (auto& x : a) scanf("%lld", &x);
    printf("%lld\n", solve(n, k, a));
    return 0;
}
