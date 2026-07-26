#include <bits/stdc++.h>
using namespace std;

vector<long long> solve(int n, vector<long long>& values, string state, long long m) {
    if (m == 0) return {};
    if (n == 0) return {};

    // best value that first becomes available exactly at release time t
    vector<long long> bucket(n, -1);
    int lastOne = -1;
    for (int i = 0; i < n; i++) {
        if (state[i] == '1') lastOne = i;
        if (lastOne != -1) {
            int release = i - lastOne;
            bucket[release] = max(bucket[release], values[i]);
        }
    }
    if (bucket[0] == -1) return {};

    long long currentMax = -1;
    for (int t = 0; t < n; t++) {
        currentMax = max(currentMax, bucket[t]);
        bucket[t] = currentMax;
    }

    vector<long long> result;
    result.reserve((size_t)m);
    for (long long step = 0; step < m; step++) {
        int index = (int)min(step, (long long)n - 1);
        if (bucket[index] == -1) return {};
        result.push_back(bucket[index]);
    }
    return result;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    if (!(cin >> n)) return 0;
    vector<long long> values(n);
    for (int i = 0; i < n; i++) cin >> values[i];
    string state;
    cin >> state;
    long long m;
    cin >> m;
    vector<long long> result = solve(n, values, state, m);
    if (result.empty()) {
        cout << "\n";
    } else {
        for (int i = 0; i < (int)result.size(); i++) {
            if (i) cout << ' ';
            cout << result[i];
        }
        cout << "\n";
    }
    return 0;
}
