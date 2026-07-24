#include <bits/stdc++.h>
using namespace std;

// Print the total of final prices, then the 0-indexed positions with no discount (increasing).
// For item i, discount = nearest price[j] (j>i) with price[j] <= price[i], else no discount.
void solve(vector<long long>& price) {
    // WRITE YOUR CODE HERE
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    if (!(cin >> n)) return 0;
    vector<long long> price(n);
    for (auto& x : price) cin >> x;
    solve(price);
    return 0;
}
