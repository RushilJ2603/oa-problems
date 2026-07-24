#include <bits/stdc++.h>
using namespace std;

// Return the number of subarrays containing exactly k odd numbers.
long long niceSubarrays(vector<int>& nums, int k) {
    // WRITE YOUR CODE HERE
    return 0;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n,k; if(!(cin>>n>>k)) return 0;
    vector<int> nums(n); for(auto& x: nums) cin>>x;
    cout << niceSubarrays(nums, k) << "\n";
    return 0;
}
