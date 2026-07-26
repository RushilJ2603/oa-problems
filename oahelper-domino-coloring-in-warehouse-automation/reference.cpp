#include <bits/stdc++.h>
using namespace std;

int solve(const string& top, const string& bottom) {
    const long long MOD = 1000000007LL;
    int n = (int)top.size();
    long long ans = 1;
    int i = 0;
    int prev = 0; // 0 = none, 1 = vertical, 2 = horizontal pair
    while (i < n) {
        if (top[i] == bottom[i]) {
            if (prev == 0) ans = (ans * 3) % MOD;
            else if (prev == 1) ans = (ans * 2) % MOD;
            // prev == 2: only 1 choice, ans unchanged
            prev = 1;
            i += 1;
        } else {
            if (prev == 0) ans = (ans * 6) % MOD;
            else if (prev == 1) ans = (ans * 2) % MOD;
            else ans = (ans * 3) % MOD;
            prev = 2;
            i += 2;
        }
    }
    return (int)ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    string top, bottom;
    if (!(cin >> top >> bottom)) return 0;
    cout << solve(top, bottom) << "\n";
    return 0;
}
