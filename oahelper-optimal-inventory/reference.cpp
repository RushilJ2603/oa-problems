#include <bits/stdc++.h>
using namespace std;

long long solve(int n, vector<long long>& quality) {
    vector<long long> uniq = quality;
    sort(uniq.begin(), uniq.end());
    uniq.erase(unique(uniq.begin(), uniq.end()), uniq.end());
    int m = (int)uniq.size();

    vector<int> ids(n), cnt(m, 0), last(m, -1);
    for (int i = 0; i < n; ++i) {
        int id = (int)(lower_bound(uniq.begin(), uniq.end(), quality[i]) - uniq.begin());
        ids[i] = id;
        ++cnt[id];
        last[id] = i;
    }

    long long keep = 0;
    int end = -1;
    int best = 0;
    for (int i = 0; i < n; ++i) {
        int id = ids[i];
        end = max(end, last[id]);
        best = max(best, cnt[id]);
        if (i == end) {
            keep += best;
            best = 0;
        }
    }
    return n - keep;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    if (!(cin >> n)) return 0;
    vector<long long> quality(n);
    for (int i = 0; i < n; i++) cin >> quality[i];
    cout << solve(n, quality) << "\n";
    return 0;
}
