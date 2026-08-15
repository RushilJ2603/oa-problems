#include <bits/stdc++.h>
using namespace std;

long long solve(long long N, int m, vector<int>& nums) {
    // WRITE YOUR CODE HERE
    return 0;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    long long N;
    if (!(cin >> N)) return 0;
    int m;
    cin >> m;
    vector<int> nums(m);
    for (int i = 0; i < m; i++) {
        cin >> nums[i];
    }
    cout << solve(N, m, nums) << "\n";
    return 0;
}
