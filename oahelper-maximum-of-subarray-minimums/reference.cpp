#include <bits/stdc++.h>
using namespace std;

long long solve(int n, vector<long long>& arr, int k) {
    deque<int> dq;
    long long best = -1;
    bool have = false;
    for (int i = 0; i < n; i++) {
        while (!dq.empty() && arr[dq.back()] >= arr[i]) {
            dq.pop_back();
        }
        dq.push_back(i);
        while (!dq.empty() && dq.front() <= i - k) {
            dq.pop_front();
        }
        if (i >= k - 1) {
            long long cur = arr[dq.front()];
            if (!have || cur > best) {
                best = cur;
                have = true;
            }
        }
    }
    return best;
}

int main() {
    ios::sync_with_stdio(false); 
    cin.tie(nullptr);
    int n; 
    if(!(cin >> n)) return 0; 
    vector<long long> arr(n); 
    for(auto& x : arr) cin >> x;
    int k; 
    cin >> k;
    cout << solve(n, arr, k) << "\n"; 
    return 0; 
}
