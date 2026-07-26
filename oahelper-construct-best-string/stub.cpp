#include <bits/stdc++.h>
using namespace std;

long long solve(int n, vector<string>& list, vector<int>& points, int limit) {
    // WRITE YOUR CODE HERE
    return 0;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    if (!(cin >> n)) return 0;
    vector<string> list(n);
    vector<int> points(n);
    for (int i = 0; i < n; ++i) cin >> list[i];
    for (int i = 0; i < n; ++i) cin >> points[i];
    int limit;
    cin >> limit;
    cout << solve(n, list, points, limit) << "\n";
    return 0;
}
