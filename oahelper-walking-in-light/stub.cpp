#include <bits/stdc++.h>
using namespace std;

string solve(int n, vector<long double>& x, vector<long double>& y,
             vector<long double>& r, long double xs, long double ys,
             long double xt, long double yt) {
    // WRITE YOUR CODE HERE
    return "NO";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    if (!(cin >> n)) return 0;
    vector<long double> x(n), y(n), r(n);
    for (int i = 0; i < n; i++) cin >> x[i] >> y[i] >> r[i];
    long double xs, ys, xt, yt;
    cin >> xs >> ys >> xt >> yt;
    cout << solve(n, x, y, r, xs, ys, xt, yt) << "\n";
    return 0;
}
