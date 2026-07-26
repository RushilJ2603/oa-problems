#include <bits/stdc++.h>
using namespace std;

string solve(const vector<vector<long long>>& operations) {
    // WRITE YOUR CODE HERE
    return "";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    if (!(cin >> n)) return 0;
    vector<vector<long long>> operations(n);
    for (int i = 0; i < n; i++) {
        long long t;
        cin >> t;
        if (t == 1) {
            long long x;
            cin >> x;
            operations[i] = {t, x};
        } else {
            long long x, size;
            cin >> x >> size;
            operations[i] = {t, x, size};
        }
    }
    cout << solve(operations) << "\n";
    return 0;
}
