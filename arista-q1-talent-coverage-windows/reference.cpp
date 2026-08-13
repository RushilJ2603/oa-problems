#include <bits/stdc++.h>
using namespace std;

vector<long long> coverageWindows(const vector<int> &talent, int talentsCount) {
    const int n = (int)talent.size();
    vector<long long> ans(n, -1);
    vector<int> seen(talentsCount + 1, 0);
    int distinct = 0;
    int r = 0;                       // one past the last student currently taken
    for (int i = 0; i < n; i++) {
        // Extend to the right until the group is complete (or the queue runs out). r never moves
        // backwards across the whole run, which is what makes this linear rather than quadratic:
        // if a group starting at i needs to reach r, one starting at i+1 cannot finish sooner.
        while (r < n && distinct < talentsCount) {
            if (++seen[talent[r]] == 1) distinct++;
            r++;
        }
        if (distinct == talentsCount) ans[i] = r - i;
        else break;                  // incomplete here means incomplete for every later start too
        if (--seen[talent[i]] == 0) distinct--;
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, talentsCount;
    if (!(cin >> n >> talentsCount)) return 0;
    vector<int> talent(n);
    for (int i = 0; i < n; i++) cin >> talent[i];
    vector<long long> ans = coverageWindows(talent, talentsCount);
    string out;
    for (int i = 0; i < n; i++) {
        if (i) out.push_back(' ');
        out += to_string(ans[i]);
    }
    out.push_back('\n');
    fwrite(out.data(), 1, out.size(), stdout);
    return 0;
}
