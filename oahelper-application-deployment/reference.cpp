#include <bits/stdc++.h>
using namespace std;

bool canSelect(const vector<long long>& v, int k, long long maxAllowed) {
    int count = 0;
    int n = (int)v.size();
    for (int i = 0; i < n; ) {
        if (v[i] <= maxAllowed) {
            count++;
            i += 2;
            if (count >= k) return true;
        } else {
            i++;
        }
    }
    return false;
}

long long solve(int n, vector<long long>& vulnerability, int k) {
    long long lo = *min_element(vulnerability.begin(), vulnerability.end());
    long long hi = *max_element(vulnerability.begin(), vulnerability.end());
    long long ans = hi;
    while (lo <= hi) {
        long long mid = lo + (hi - lo) / 2;
        if (canSelect(vulnerability, k, mid)) {
            ans = mid;
            hi = mid - 1;
        } else {
            lo = mid + 1;
        }
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    if (!(cin >> n)) return 0;
    vector<long long> vulnerability(n);
    for (int i = 0; i < n; i++) cin >> vulnerability[i];
    int k;
    cin >> k;
    cout << solve(n, vulnerability, k) << "\n";
    return 0;
}
