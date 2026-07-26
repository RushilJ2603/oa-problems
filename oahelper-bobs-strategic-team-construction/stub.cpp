#include <bits/stdc++.h>
using namespace std;

long long solve(int n, int m, int k, vector<int>& salary, vector<long long>& earning) {
    // WRITE YOUR CODE HERE
    return 0;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m, k;
    if (!(cin >> n >> m >> k)) return 0;
    vector<int> salary(n);
    vector<long long> earning(n);
    for (int i = 0; i < n; ++i) cin >> salary[i];
    for (int i = 0; i < n; ++i) cin >> earning[i];
    cout << solve(n, m, k, salary, earning) << "\n";
    return 0;
}
