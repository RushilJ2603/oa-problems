#include <bits/stdc++.h>
using namespace std;

vector<int> solve(vector<int>& modifiedUnits, vector<string>& accessRights) {
    int n = (int)accessRights.size();
    if (n == 0) return {-1};
    int m = (int)accessRights[0].size();
    if (m == 0) return {-1};
    vector<char> tampered(m, 0);
    for (int u : modifiedUnits) tampered[u - 1] = 1;
    vector<char> pot(n, 1);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (accessRights[i][j] == '1' && !tampered[j]) {
                pot[i] = 0;
                break;
            }
        }
    }
    vector<int> pot_count(m, 0);
    for (int i = 0; i < n; ++i) if (pot[i]) {
        for (int j = 0; j < m; ++j)
            if (accessRights[i][j] == '1') pot_count[j]++;
    }
    vector<int> result;
    for (int i = 0; i < n; ++i) if (pot[i]) {
        bool assured = false;
        for (int j = 0; j < m; ++j) {
            if (accessRights[i][j] == '1' && pot_count[j] == 1) {
                assured = true;
                break;
            }
        }
        if (assured) result.push_back(i + 1);
    }
    if (result.empty()) return {-1};
    return result;
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
