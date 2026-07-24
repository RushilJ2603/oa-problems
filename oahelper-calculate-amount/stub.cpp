#include <bits/stdc++.h>
using namespace std;

// Return Priya's total cost: cost[0]=prices[0]; cost[i]=max(0, prices[i]-min(prices[0..i-1])).
long long calculateAmount(vector<long long>& prices) {
    // WRITE YOUR CODE HERE
    return 0;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    if (!(cin >> n)) return 0;
    vector<long long> prices(n);
    for (auto& x : prices) cin >> x;
    cout << calculateAmount(prices) << "\n";
    return 0;
}
