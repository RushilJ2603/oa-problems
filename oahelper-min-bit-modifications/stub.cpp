#include <bits/stdc++.h>
using namespace std;

// Minimum total single-bit flips to make every element equal.
long long minFlips(vector<unsigned long long>& a) {
    // WRITE YOUR CODE HERE
    return 0;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    if (!(cin >> n)) return 0;
    vector<unsigned long long> a(n);
    for (auto& x : a) cin >> x;
    cout << minFlips(a) << "\n";
    return 0;
}
