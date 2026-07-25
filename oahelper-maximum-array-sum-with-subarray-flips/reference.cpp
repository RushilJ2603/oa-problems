#include <bits/stdc++.h>
using namespace std;

const long long INF = 1e17;

struct State {
    long long sum;
    long long count;

    bool operator>(const State& other) const {
        if (sum != other.sum) return sum > other.sum;
        return count < other.count;
    }
};

State check(long long cost, const vector<long long>& b) {
    State dp0 = {0, 0};
    State dp1 = {-INF, 0};

    for (long long x : b) {
        State new_dp0 = (dp0 > dp1) ? dp0 : dp1;

        State cand1 = {dp1.sum + x, dp1.count};
        State cand2 = {dp0.sum + x - cost, dp0.count + 1};

        State new_dp1 = (cand1 > cand2) ? cand1 : cand2;

        dp0 = new_dp0;
        dp1 = new_dp1;
    }

    return (dp0 > dp1) ? dp0 : dp1;
}

long long solve(int n, long long k, vector<long long>& a) {
    vector<long long> b(n);
    long long sum_a = 0;
    long long max_abs_b = 0;

    for (int i = 0; i < n; ++i) {
        b[i] = -a[i];
        sum_a += a[i];
        max_abs_b += (b[i] < 0 ? -b[i] : b[i]);
    }

    State res0 = check(0, b);
    if (res0.count <= k) {
        return sum_a + 2 * res0.sum;
    }

    long long l = 0, r = max_abs_b + 1;
    long long best_val = 0;

    while (l <= r) {
        long long m = l + (r - l) / 2;
        State res = check(m, b);

        if (res.count <= k) {
            best_val = res.sum + m * k;
            r = m - 1;
        } else {
            l = m + 1;
        }
    }

    return sum_a + 2 * best_val;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    long long k;
    if (!(cin >> n >> k)) return 0;
    vector<long long> a(n);
    for (int i = 0; i < n; ++i) cin >> a[i];
    cout << solve(n, k, a) << "\n";
    return 0;
}
