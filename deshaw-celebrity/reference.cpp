#include <bits/stdc++.h>
using namespace std;

// Candidate-elimination: one linear pass narrows to a single possible celebrity, then one pass
// verifies it. O(n) comparisons after the matrix is read.
int celebrity(int n, const vector<vector<int>>& knows) {
    int cand = 0;
    for (int i = 1; i < n; i++)
        if (knows[cand][i]) cand = i;          // cand knows i => cand isn't the celebrity
    for (int i = 0; i < n; i++) {
        if (i == cand) continue;
        if (knows[cand][i] || !knows[i][cand]) return -1;
    }
    return cand;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    if (!(cin >> n)) return 0;
    vector<vector<int>> knows(n, vector<int>(n));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) cin >> knows[i][j];
    cout << celebrity(n, knows) << "\n";
    return 0;
}
