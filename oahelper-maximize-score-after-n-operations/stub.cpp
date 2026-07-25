#include <bits/stdc++.h>
using namespace std;

long long solve(int m, vector<long long>& nums) {
    // WRITE YOUR CODE HERE
    return 0;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int m;
    if (!(cin >> m)) return 0;
    vector<long long> nums(m);
    for (int i = 0; i < m; i++) cin >> nums[i];
    cout << solve(m, nums) << "\n";
    return 0;
}
