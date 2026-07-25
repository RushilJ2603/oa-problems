#include <bits/stdc++.h>
using namespace std;

int solve(int n, vector<int>& t) {
    vector<int> counts(n + 1, 0);
    for (int x : t) counts[x]++;
    int ans = 0;
    int less = 0;
    for (int O = 0; O <= n; O++) {
        // O operating robots valid iff:
        // exactly O robots have threshold <= O-1 (i.e. less), and none have threshold == O
        // For O=0: less==0 and counts[0]==0 means all thresholds > 0
        if (counts[O] == 0 && less == O) ans++;
        less += counts[O];
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    if (!(cin >> n)) return 0;
    vector<int> t(n);
    for (int i = 0; i < n; i++) cin >> t[i];
    cout << solve(n, t) << "\n";
    return 0;
}
