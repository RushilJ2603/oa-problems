#include <bits/stdc++.h>
using namespace std;

pair<long long, long long> solve(int n, vector<long long>& a, vector<long long>& b,
                                 vector<long long>& c) {
    // WRITE YOUR CODE HERE
    return {0, 0};
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    if (!(cin >> T)) return 0;
    while (T--) {
        int n;
        cin >> n;
        vector<long long> a(n), b(n), c(n);
        for (auto& x : a) cin >> x;
        for (auto& x : b) cin >> x;
        for (auto& x : c) cin >> x;
        auto [m, cost] = solve(n, a, b, c);
        cout << m << ' ' << cost << '\n';
    }
    return 0;
}
