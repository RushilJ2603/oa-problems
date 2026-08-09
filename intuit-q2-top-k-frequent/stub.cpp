#include <bits/stdc++.h>
using namespace std;

vector<string> topKFrequent(const vector<string> &tags, int k) {
    // WRITE YOUR CODE HERE
    return {};
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    if (!(cin >> n)) return 0;
    vector<string> tags(n);
    for (int i = 0; i < n; i++) cin >> tags[i];
    int k;
    cin >> k;

    vector<string> ans = topKFrequent(tags, k);
    for (size_t i = 0; i < ans.size(); i++) cout << ans[i] << (i + 1 < ans.size() ? ' ' : '\n');
    if (ans.empty()) cout << "\n";
    return 0;
}
