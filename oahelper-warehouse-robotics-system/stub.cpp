#include <bits/stdc++.h>
using namespace std;

int solve(int n, vector<int>& t) {
    // WRITE YOUR CODE HERE
    return 0;
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
