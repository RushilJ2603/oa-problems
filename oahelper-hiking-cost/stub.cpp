#include <bits/stdc++.h>
using namespace std;

long long solve(int n, vector<long long>& a) {
    // WRITE YOUR CODE HERE
    return 0;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    if (!(cin >> n)) return 0;
    vector<long long> a(n);
    for (auto& x : a) cin >> x;
    cout << solve(n, a) << "\n";
    return 0;
}
