#include <bits/stdc++.h>
using namespace std;

long long solve(vector<int>& supplierStock, long long orders) {
    // WRITE YOUR CODE HERE
    return 0;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    if (!(cin >> n)) return 0;
    vector<int> stock(n);
    for (int i = 0; i < n; ++i) cin >> stock[i];
    long long orders;
    cin >> orders;
    cout << solve(stock, orders) << "\n";
    return 0;
}
