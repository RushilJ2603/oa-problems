#include <bits/stdc++.h>
using namespace std;

long long solve(int n, vector<long long>& impact, vector<vector<int>>& precells) {
    // WRITE YOUR CODE HERE
    return 0;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    if (!(cin >> n)) return 0;
    vector<long long> impact(n);
    vector<vector<int>> precells(n);
    for (int i = 0; i < n; i++) {
        int k;
        cin >> impact[i] >> k;
        precells[i].resize(k);
        for (int j = 0; j < k; j++) {
            cin >> precells[i][j];
            precells[i][j]--;
        }
    }
    cout << solve(n, impact, precells) << "\n";
    return 0;
}
