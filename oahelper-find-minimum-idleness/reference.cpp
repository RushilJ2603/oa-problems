#include <bits/stdc++.h>
using namespace std;

int solve(const string& shader, int switchCount) {
    vector<int> runs;
    int n = (int)shader.size();
    for (int i = 0; i < n; ) {
        int j = i;
        while (j < n && shader[j] == shader[i]) ++j;
        runs.push_back(j - i);
        i = j;
    }
    int lo = 1, hi = n;
    while (lo < hi) {
        int mid = (lo + hi) / 2;
        long long cost = 0;
        for (int L : runs) cost += L / (mid + 1);
        if (cost <= switchCount) hi = mid;
        else lo = mid + 1;
    }
    return lo;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    string shader;
    int switchCount;
    if (!(cin >> shader >> switchCount)) return 0;
    cout << solve(shader, switchCount) << "\n";
    return 0;
}
