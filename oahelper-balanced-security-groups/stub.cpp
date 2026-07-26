#include <bits/stdc++.h>
using namespace std;

int solve(int n, vector<int>& security) {
    // WRITE YOUR CODE HERE
    return 0;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    if (!(cin >> n)) return 0;
    vector<int> security(n);
    for (int i = 0; i < n; i++) cin >> security[i];
    cout << solve(n, security) << "\n";
    return 0;
}
