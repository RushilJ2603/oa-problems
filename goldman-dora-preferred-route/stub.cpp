#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<vector<int>> g(n, vector<int>(n));
    for (auto& row : g) for (auto& x : row) cin >> x;
    int S, D;
    cin >> S >> D;
    // Print the longest simple path S..D (max cities); ties -> lexicographically smallest.
    // your code here
    return 0;
}
