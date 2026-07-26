#include <bits/stdc++.h>
using namespace std;

int solve(vector<int>& weights, long long max_wt) {
    vector<long long> w(weights.begin(), weights.end());
    sort(w.begin(), w.end());
    int n = (int)w.size();
    int idx = n - 1;
    long long capacity = max_wt;
    int shipped = 0;
    while (idx >= 0 && capacity > 0) {
        if (w[idx] >= capacity) {
            idx--;
        } else {
            shipped++;
            idx--;
            capacity--;
        }
    }
    return n - shipped;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    if (!(cin >> n)) return 0;
    vector<int> weights(n);
    for (int i = 0; i < n; i++) cin >> weights[i];
    long long max_wt;
    cin >> max_wt;
    cout << solve(weights, max_wt) << "\n";
    return 0;
}
