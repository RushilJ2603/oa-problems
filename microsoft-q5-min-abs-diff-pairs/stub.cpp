#include <bits/stdc++.h>
using namespace std;

// Return the pairs (x, y) with x < y achieving the minimum absolute difference,
// sorted ascending by x then y.
vector<pair<long long,long long>> solve(vector<long long> a) {
    // WRITE YOUR CODE HERE
    return {};
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    if (!(cin >> n)) return 0;
    vector<long long> a(n);
    for (auto &x : a) cin >> x;
    for (auto &p : solve(a)) cout << p.first << " " << p.second << "\n";
    return 0;
}
