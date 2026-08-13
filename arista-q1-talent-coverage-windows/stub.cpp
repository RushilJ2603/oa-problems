#include <bits/stdc++.h>
using namespace std;

vector<long long> coverageWindows(const vector<int> &talent, int talentsCount) {
    // WRITE YOUR CODE HERE
    return vector<long long>(talent.size(), -1);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, talentsCount;
    if (!(cin >> n >> talentsCount)) return 0;
    vector<int> talent(n);
    for (int i = 0; i < n; i++) cin >> talent[i];
    vector<long long> ans = coverageWindows(talent, talentsCount);
    for (int i = 0; i < (int)ans.size(); i++) cout << (i ? " " : "") << ans[i];
    cout << "\n";
    return 0;
}
