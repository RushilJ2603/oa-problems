#include <bits/stdc++.h>
using namespace std;

int solve(int n, string& s, int k) {
    int best = 0;
    for (int t = 0; t < 2; ++t) {
        char target = (t == 0 ? '0' : '1');
        int bad = 0, left = 0;
        for (int right = 0; right < n; ++right) {
            if (s[right] != target) ++bad;
            while (bad > k) {
                if (s[left] != target) --bad;
                ++left;
            }
            best = max(best, right - left + 1);
        }
    }
    return best;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, k;
    string s;
    if (!(cin >> n)) return 0;
    cin >> s >> k;
    cout << solve(n, s, k) << "\n";
    return 0;
}
