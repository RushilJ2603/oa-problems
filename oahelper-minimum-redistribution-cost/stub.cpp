#include <bits/stdc++.h>
using namespace std;

long long calculateMinimumRedistributionCost(vector<int>& products) {
    // WRITE YOUR CODE HERE
    return 0;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    if (!(cin >> n)) return 0;
    vector<int> products(n);
    for (int i = 0; i < n; i++) cin >> products[i];
    cout << calculateMinimumRedistributionCost(products) << "\n";
    return 0;
}
