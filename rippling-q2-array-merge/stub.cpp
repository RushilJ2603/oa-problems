#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<long long> X(n);
    for (auto& x : X) cin >> x;
    int m;
    cin >> m;
    vector<long long> Y(m);
    for (auto& y : Y) cin >> y;
    // Minimum operations (replace a subarray with its sum) to make X and Y identical, or -1.
    // your code here
    return 0;
}
