#include <bits/stdc++.h>
using namespace std;

// Return the maximum coins from bursting all balloons (nums[i-1]*nums[i]*nums[i+1]).
long long maxCoins(vector<long long>& nums) {
    // WRITE YOUR CODE HERE
    return 0;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n; if(!(cin>>n)) return 0;
    vector<long long> nums(n); for(auto& x: nums) cin>>x;
    cout << maxCoins(nums) << "\n";
    return 0;
}
