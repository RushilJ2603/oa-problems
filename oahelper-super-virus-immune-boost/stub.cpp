#include <bits/stdc++.h>
using namespace std;

long long solve(int x, vector<long long>& boost, vector<vector<int>>& prereq) {
    // WRITE YOUR CODE HERE
    return 0;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int x;
    if (!(cin >> x)) return 0;
    vector<long long> boost(x + 1);
    vector<vector<int>> prereq(x + 1);
    for (int i = 1; i <= x; i++) {
        long long b;
        int m;
        cin >> b >> m;
        boost[i] = b;
        prereq[i].resize(m);
        for (int j = 0; j < m; j++) cin >> prereq[i][j];
    }
    cout << solve(x, boost, prereq) << "\n";
    return 0;
}
