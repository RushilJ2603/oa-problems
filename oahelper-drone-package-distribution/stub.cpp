#include <bits/stdc++.h>
using namespace std;

long long solve(int N, vector<pair<int,int>>& packages,
                int totalZones, int maxPackages, int maxWeight) {
    // WRITE YOUR CODE HERE
    return 0;
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
