#include <bits/stdc++.h>
using namespace std;

string solve(const vector<vector<long long>>& operations) {
    set<long long> obstacles;
    string result;
    for (const auto& op : operations) {
        if (op[0] == 1) {
            obstacles.insert(op[1]);
        } else {
            long long x = op[1];
            long long size = op[2];
            long long lo = x - size;
            long long hi = x - 1;
            auto it = obstacles.lower_bound(lo);
            if (it != obstacles.end() && *it <= hi) {
                result.push_back('0');
            } else {
                result.push_back('1');
            }
        }
    }
    return result;
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
