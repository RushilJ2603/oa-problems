#include <bits/stdc++.h>
using namespace std;

long long solve(int n, long long m, long long t, long long k,
                const vector<pair<long long, long long>>& B) {
    // WRITE YOUR CODE HERE
    return -1;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    if (!(cin >> T)) return 0;
    while (T--) {
        int n;
        long long m, t, k;
        cin >> n >> m >> t >> k;
        vector<pair<long long, long long>> B(n);
        for (int i = 0; i < n; i++) cin >> B[i].first >> B[i].second;
        cout << solve(n, m, t, k, B) << "\n";
    }
    return 0;
}
