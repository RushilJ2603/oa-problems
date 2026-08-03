#include <bits/stdc++.h>
using namespace std;

long long solve(int n, vector<int>& w) {
    // WRITE YOUR CODE HERE
    return 0;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    if (!(cin >> n)) return 0;
    vector<int> w(n);
    for (auto& x : w) cin >> x;
    cout << solve(n, w) << "\n";
    return 0;
}
