#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<long long> p(n), r(n);
    for (auto& x : p) cin >> x;
    for (auto& x : r) cin >> x;
    // For each sensor, print the minimum increment to its range so it overlaps some other sensor
    // (others kept at their original ranges). See the statement for the exact rule.
    // your code here
    return 0;
}
