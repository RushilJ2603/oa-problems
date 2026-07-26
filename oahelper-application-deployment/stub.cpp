#include <bits/stdc++.h>
using namespace std;

long long solve(int n, vector<long long>& vulnerability, int k) {
    // WRITE YOUR CODE HERE
    return 0;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    if (!(cin >> n)) return 0;
    vector<long long> vulnerability(n);
    for (int i = 0; i < n; i++) cin >> vulnerability[i];
    int k;
    cin >> k;
    cout << solve(n, vulnerability, k) << "\n";
    return 0;
}
