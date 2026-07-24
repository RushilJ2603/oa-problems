#include <bits/stdc++.h>
using namespace std;

// Return the number of subarrays whose XOR equals k.
long long countXorK(vector<long long>& nums, long long k) {
    // WRITE YOUR CODE HERE
    return 0;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n; long long k; if(!(cin>>n>>k)) return 0;
    vector<long long> nums(n); for(auto& x: nums) cin>>x;
    cout << countXorK(nums, k) << "\n";
    return 0;
}
