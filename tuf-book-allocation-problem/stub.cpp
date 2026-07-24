#include <bits/stdc++.h>
using namespace std;

// Return the minimised maximum pages over m contiguous allocations, or -1 if m>n.
long long minMaxPages(vector<long long>& nums, int m) {
    // WRITE YOUR CODE HERE
    return -1;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n,m; if(!(cin>>n>>m)) return 0;
    vector<long long> nums(n); for(auto& x: nums) cin>>x;
    cout << minMaxPages(nums, m) << "\n";
    return 0;
}
