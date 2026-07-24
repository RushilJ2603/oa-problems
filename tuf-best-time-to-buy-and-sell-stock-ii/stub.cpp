#include <bits/stdc++.h>
using namespace std;

// Return the max total profit with unlimited buy/sell (hold <=1 share).
long long maxProfit(vector<long long>& arr) {
    // WRITE YOUR CODE HERE
    return 0;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n; if(!(cin>>n)) return 0;
    vector<long long> arr(n); for(auto& x: arr) cin>>x;
    cout << maxProfit(arr) << "\n";
    return 0;
}
