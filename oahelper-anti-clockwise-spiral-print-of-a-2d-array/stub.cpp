#include <bits/stdc++.h>
using namespace std;

vector<int> solve(int R, int C, const vector<vector<int>>& mat) {
    // WRITE YOUR CODE HERE
    return {};
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int r, c;
    if (!(cin >> r >> c)) return 0;
    vector<vector<int>> mat(r, vector<int>(c));
    for (int i = 0; i < r; ++i) {
        for (int j = 0; j < c; ++j) {
            cin >> mat[i][j];
        }
    }
    vector<int> res = solve(r, c, mat);
    for (size_t i = 0; i < res.size(); ++i) {
        cout << res[i] << (i + 1 == res.size() ? "" : " ");
    }
    cout << "\n";
    return 0;
}
