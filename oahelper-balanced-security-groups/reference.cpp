#include <bits/stdc++.h>
using namespace std;

int solve(int n, vector<int>& security) {
    if (n == 0) return 0;
    unordered_map<int, int> freq;
    freq.reserve(n * 2);
    for (int x : security) freq[x]++;

    vector<int> counts;
    counts.reserve(freq.size());
    int min_c = n;
    for (auto& [_, c] : freq) {
        counts.push_back(c);
        if (c < min_c) min_c = c;
    }

    // Largest valid base size s minimizes the number of groups.
    for (int s = min_c; s >= 1; --s) {
        bool ok = true;
        long long total = 0;
        for (int c : counts) {
            // Minimum groups if each has size at most s+1: ceil(c / (s+1))
            int g = (c + s) / (s + 1);
            // Valid iff those groups can each have size at least s
            if ((long long)g * s > c) {
                ok = false;
                break;
            }
            total += g;
        }
        if (ok) return (int)total;
    }
    return 0;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    if (!(cin >> n)) return 0;
    vector<int> security(n);
    for (int i = 0; i < n; i++) cin >> security[i];
    cout << solve(n, security) << "\n";
    return 0;
}
