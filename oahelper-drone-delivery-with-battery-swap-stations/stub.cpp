#include <bits/stdc++.h>
using namespace std;

int solve(int rows, int cols, vector<vector<int>>& grid,
          int sr, int sc, int er, int ec, int B,
          vector<pair<int,int>>& stations, int K) {
    // WRITE YOUR CODE HERE
    return -1;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int rows, cols;
    if (!(cin >> rows >> cols)) return 0;
    vector<vector<int>> grid(rows, vector<int>(cols));
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            cin >> grid[i][j];
    int sr, sc, er, ec, B, M, K;
    cin >> sr >> sc >> er >> ec >> B >> M;
    vector<pair<int,int>> stations(M);
    for (int i = 0; i < M; i++)
        cin >> stations[i].first >> stations[i].second;
    cin >> K;
    cout << solve(rows, cols, grid, sr, sc, er, ec, B, stations, K) << "\n";
    return 0;
}
