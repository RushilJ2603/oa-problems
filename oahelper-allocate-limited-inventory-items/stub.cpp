#include <bits/stdc++.h>
using namespace std;

vector<int> solve(vector<vector<long long>>& requests, long long totalInventory) {
    // WRITE YOUR CODE HERE
    return {};
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    if (!(cin >> n)) return 0;
    int cols;
    cin >> cols;
    vector<vector<long long>> requests(n, vector<long long>(cols));
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < cols; ++j)
            cin >> requests[i][j];
    long long totalInventory;
    cin >> totalInventory;
    vector<int> res = solve(requests, totalInventory);
    for (size_t i = 0; i < res.size(); ++i) {
        if (i) cout << ' ';
        cout << res[i];
    }
    cout << "\n";
    return 0;
}
