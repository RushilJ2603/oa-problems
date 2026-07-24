#include <bits/stdc++.h>
using namespace std;

// Return the maximum achievable minimum distance placing k cows in the stalls.
long long maxMinDist(vector<long long>& nums, int k) {
    // WRITE YOUR CODE HERE
    return 0;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n,k; if(!(cin>>n>>k)) return 0;
    vector<long long> nums(n); for(auto& x: nums) cin>>x;
    cout << maxMinDist(nums, k) << "\n";
    return 0;
}
