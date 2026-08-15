#include <bits/stdc++.h>
using namespace std;

long long solve(long long N, int m, vector<int>& nums) {
    sort(nums.begin(), nums.end());
    nums.erase(unique(nums.begin(), nums.end()), nums.end());

    auto lowerBoundValue = [&](long long factor) -> long long {
        auto it = lower_bound(nums.begin(), nums.end(), factor);
        if (it == nums.begin()) return 0;
        --it;
        return *it;
    };

    long long ans = 0;
    for (long long i = 1; i * i <= N; ++i) {
        if (N % i == 0) {
            ans += lowerBoundValue(i);
            if (i * i != N) {
                ans += lowerBoundValue(N / i);
            }
        }
    }
    return ans;
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
