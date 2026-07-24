#include <bits/stdc++.h>
using namespace std;

// Return the number of inversions (i<j with nums[i]>nums[j]).
long long countInversions(vector<long long>& nums) {
    // WRITE YOUR CODE HERE
    return 0;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n; if(!(cin>>n)) return 0;
    vector<long long> nums(n); for(auto& x: nums) cin>>x;
    cout << countInversions(nums) << "\n";
    return 0;
}
