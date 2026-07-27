#include <bits/stdc++.h>
using namespace std;

// Each ')' -> "()" replacement adds exactly one '(' and keeps the ')' count the same.
// So to balance the counts we must upgrade exactly need = closes - opens closers
// (need must be in [0, k]).  Scanning left to right, a ')' seen while the running
// balance is 0 MUST be upgraded (otherwise the prefix goes negative); that count is
// the forced minimum.  Any remaining upgrades (need - forced) can be spent on other
// closers harmlessly.  Feasible iff forced <= need.
int solve(const string &s, long long k) {
    long long opens = 0, closes = 0;
    for (char c : s) (c == '(' ? opens : closes)++;
    long long need = closes - opens;
    if (need < 0 || need > k) return 0;
    long long bal = 0, forced = 0;
    for (char c : s) {
        if (c == '(') bal++;
        else if (bal > 0) bal--;
        else forced++;              // forced upgrade; balance returns to its prior value
    }
    return forced <= need ? 1 : 0;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    string s; long long k;
    if (!(cin >> s)) return 0;
    cin >> k;
    cout << solve(s, k) << "\n";
}
