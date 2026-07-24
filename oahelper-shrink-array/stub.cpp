#include <bits/stdc++.h>
using namespace std;

// Collapse each equal-value group to its middle position, holding the group's sum.
vector<long long> shrink(vector<long long>& A) {
    // WRITE YOUR CODE HERE
    return A;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    if (!(cin >> n)) return 0;
    vector<long long> A(n);
    for (auto& x : A) cin >> x;
    vector<long long> res = shrink(A);
    for (size_t i = 0; i < res.size(); ++i) cout << res[i] << " \n"[i + 1 == res.size()];
    return 0;
}
