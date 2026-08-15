#include <bits/stdc++.h>
using namespace std;

vector<int> solve(int R, int C, const vector<vector<int>>& mat) {
    vector<int> result;
    if (R == 0 || C == 0) return result;
    int top = 0, bottom = R - 1;
    int left = 0, right = C - 1;
    
    while (top <= bottom && left <= right) {
        for (int i = top; i <= bottom; ++i) {
            result.push_back(mat[i][left]);
        }
        left++;
        
        if (top <= bottom && left <= right) {
            for (int i = left; i <= right; ++i) {
                result.push_back(mat[bottom][i]);
            }
            bottom--;
        }
        
        if (top <= bottom && left <= right) {
            for (int i = bottom; i >= top; --i) {
                result.push_back(mat[i][right]);
            }
            right--;
        }
        
        if (top <= bottom && left <= right) {
            for (int i = right; i >= left; --i) {
                result.push_back(mat[top][i]);
            }
            top++;
        }
    }
    return result;
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
