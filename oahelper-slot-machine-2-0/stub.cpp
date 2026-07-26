#include <bits/stdc++.h>
using namespace std;

int solve(vector<string>& history) {
    // WRITE YOUR CODE HERE
    return 0;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    if (!(cin >> n)) return 0;
    vector<string> history(n);
    for (int i = 0; i < n; ++i) cin >> history[i];
    cout << solve(history) << "\n";
    return 0;
}
