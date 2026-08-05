// Cheapest way to leave three regions holding three required machine counts.
//
// The shape of any plan is forced. A region that transfers its machines away is spent, so every
// region ends up in exactly one of four roles: it is the region that will hold target 0, or target
// 1, or target 2, or it is left alone. A region assigned to a target either holds it directly or
// has other assigned regions poured into it — and once you know WHICH regions form a target's
// group, the cost is fixed and does not depend on which of them is the survivor:
//
//     cost(group, target) = (|group| - 1) * shiftingCost   [one transfer per region poured in]
//                         + |sum(group) - target|          [one unit per machine added or removed]
//
// So the answer is a minimum over ways to label each region with {target 0, 1, 2, unused}, subject
// to every target getting at least one region. With n <= 10 that is at most 4^10 = 1,048,576
// labellings, which is small enough to walk directly; the labelling already covers every way of
// matching regions to targets, so no separate permutation loop is needed.
//
// 64-bit throughout: ten regions of 10^9 machines sum to 10^10, which does not fit in an int.
#include <bits/stdc++.h>
using namespace std;

long long minTransformCost(const vector<long long> &machines, const vector<long long> &finals,
                           long long shiftingCost) {
    int n = (int)machines.size();
    long long total = 1;
    for (int i = 0; i < n; i++) total *= 4;

    long long best = LLONG_MAX;
    vector<long long> sum(3);
    vector<int> cnt(3);
    for (long long code = 0; code < total; code++) {
        sum[0] = sum[1] = sum[2] = 0;
        cnt[0] = cnt[1] = cnt[2] = 0;
        long long c = code;
        for (int i = 0; i < n; i++) {
            int lab = (int)(c & 3);
            c >>= 2;
            if (lab < 3) { sum[lab] += machines[i]; cnt[lab]++; }
        }
        if (!cnt[0] || !cnt[1] || !cnt[2]) continue;      // each target needs a region to live in
        long long cost = 0;
        for (int t = 0; t < 3; t++)
            cost += (long long)(cnt[t] - 1) * shiftingCost + llabs(sum[t] - finals[t]);
        best = min(best, cost);
    }
    return best;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    if (!(cin >> n)) return 0;
    vector<long long> machines(n), finals(3);
    for (int i = 0; i < n; i++) cin >> machines[i];
    for (int i = 0; i < 3; i++) cin >> finals[i];
    long long shiftingCost;
    cin >> shiftingCost;
    cout << minTransformCost(machines, finals, shiftingCost) << "\n";
    return 0;
}
