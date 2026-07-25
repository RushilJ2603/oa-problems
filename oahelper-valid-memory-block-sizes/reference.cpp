#include <bits/stdc++.h>
using namespace std;

vector<int> solve(vector<int> memoryBlocks) {
    int n = (int)memoryBlocks.size();
    vector<int> C(n + 2, 0);

    for (int x : memoryBlocks) {
        if (x >= 0 && x < n + 2) C[x]++;
    }

    int m = 0;
    while (m < n + 2 && C[m] > 0) m++;

    int m2 = m + 1;
    while (m2 < n + 2 && C[m2] > 0) m2++;

    vector<bool> possible(n + 2, false);
    if (m < n + 2) possible[m] = true;

    for (int v = 0; v < n + 2; v++) {
        if (C[v] > 0 && v < n - 1) {
            if (v < m && C[v] == 1) possible[v] = true;
            if (v == m - 1 && C[v] > 1) {
                if (m2 < n + 2) possible[m2] = true;
            }
        }
    }

    vector<int> ans;
    for (int i = 0; i < n + 2; i++) {
        if (possible[i]) ans.push_back(i);
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    if (!(cin >> n)) return 0;
    vector<int> memoryBlocks(n);
    for (int i = 0; i < n; i++) cin >> memoryBlocks[i];
    vector<int> result = solve(memoryBlocks);
    for (int i = 0; i < (int)result.size(); i++) {
        if (i) cout << " ";
        cout << result[i];
    }
    cout << "\n";
    return 0;
}
