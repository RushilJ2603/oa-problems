#include <bits/stdc++.h>
using namespace std;

long long solve(int n, vector<long long>& quality) {
    // WRITE YOUR CODE HERE
    return 0;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    if (!(cin >> n)) return 0;
    vector<long long> quality(n);
    for (int i = 0; i < n; i++) cin >> quality[i];
    cout << solve(n, quality) << "\n";
    return 0;
}
