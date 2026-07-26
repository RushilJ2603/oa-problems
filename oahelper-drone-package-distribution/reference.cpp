#include <bits/stdc++.h>
using namespace std;

long long solve(int N, const vector<pair<int,int>>& packages,
                int /*totalZones*/, int maxPackages, int maxWeight) {
    vector<int> zone(N + 1), changes(N + 1, 0);
    vector<long long> prefixWeight(N + 1, 0), dp(N + 1, 0);
    for (int i = 1; i <= N; ++i) {
        zone[i] = packages[i - 1].first;
        prefixWeight[i] = prefixWeight[i - 1] + packages[i - 1].second;
        if (i > 1) changes[i] = changes[i - 1] + (zone[i] != zone[i - 1]);
    }
    deque<int> dq;
    dq.push_back(1);
    for (int i = 1; i <= N; ++i) {
        while (!dq.empty() &&
               (i - dq.front() + 1 > maxPackages ||
                prefixWeight[i] - prefixWeight[dq.front() - 1] > maxWeight)) {
            dq.pop_front();
        }
        dp[i] = dp[dq.front() - 1] + 2 + changes[i] - changes[dq.front()];
        if (i < N) {
            long long currentValue = dp[i] - changes[i + 1];
            while (!dq.empty()) {
                int j = dq.back();
                long long backValue = dp[j - 1] - changes[j];
                if (backValue >= currentValue) dq.pop_back();
                else break;
            }
            dq.push_back(i + 1);
        }
    }
    return dp[N];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int N;
    if (!(cin >> N)) return 0;
    vector<pair<int,int>> packages(N);
    for (int i = 0; i < N; ++i) cin >> packages[i].first >> packages[i].second;
    int totalZones, maxPackages, maxWeight;
    cin >> totalZones >> maxPackages >> maxWeight;
    cout << solve(N, packages, totalZones, maxPackages, maxWeight) << "\n";
    return 0;
}
