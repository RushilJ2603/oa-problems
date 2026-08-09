#include <bits/stdc++.h>
using namespace std;

// Count, then order by (count desc, word asc). nth_element would be enough for top-k, but n is only
// 2e5 so a full sort is comfortably inside the limit and is easier to read.
vector<string> topKFrequent(const vector<string> &tags, int k) {
    unordered_map<string, int> freq;
    freq.reserve(tags.size() * 2);
    for (const string &t : tags) freq[t]++;

    vector<pair<string, int>> items(freq.begin(), freq.end());
    sort(items.begin(), items.end(), [](const pair<string, int> &a, const pair<string, int> &b) {
        if (a.second != b.second) return a.second > b.second;
        return a.first < b.first;
    });

    vector<string> out;
    for (int i = 0; i < k && i < (int)items.size(); i++) out.push_back(items[i].first);
    return out;
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
