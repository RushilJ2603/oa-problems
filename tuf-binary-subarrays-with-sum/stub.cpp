#include <bits/stdc++.h>
using namespace std;

// Return the number of subarrays of the 0/1 array nums whose sum equals goal.
long long numSubarrays(vector<int>& nums, int goal) {
    // WRITE YOUR CODE HERE
    return 0;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n,goal; if(!(cin>>n>>goal)) return 0;
    vector<int> nums(n); for(auto& x: nums) cin>>x;
    cout << numSubarrays(nums, goal) << "\n";
    return 0;
}
