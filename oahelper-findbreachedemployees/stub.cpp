#include <bits/stdc++.h>
using namespace std;

vector<int> solve(vector<int>& modifiedUnits, vector<string>& accessRights) {
    // WRITE YOUR CODE HERE
    return {-1};
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int k;
    if (!(cin >> k)) return 0;
    vector<int> modifiedUnits(k);
    for (int i = 0; i < k; ++i) cin >> modifiedUnits[i];
    int n; cin >> n;
    vector<string> accessRights(n);
    for (int i = 0; i < n; ++i) cin >> accessRights[i];
    auto res = solve(modifiedUnits, accessRights);
    for (int x : res) cout << x << "\n";
    return 0;
}
