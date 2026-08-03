#include <bits/stdc++.h>
using namespace std;

string solve(int M, int N, vector<vector<int>>& grid, int startR, int startC, long long Z,
             const set<pair<int, int>>& safeCells) {
    // WRITE YOUR CODE HERE
    return "0";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int M, N;
    if (!(cin >> M >> N)) return 0;
    vector<vector<int>> grid(M, vector<int>(N));
    for (int i = 0; i < M; i++)
        for (int j = 0; j < N; j++) cin >> grid[i][j];
    int sr, sc;
    long long Z;
    cin >> sr >> sc >> Z;
    int S;
    cin >> S;
    set<pair<int, int>> safe;
    for (int i = 0; i < S; i++) {
        int r, c;
        cin >> r >> c;
        safe.insert({r, c});
    }
    cout << solve(M, N, grid, sr, sc, Z, safe) << "\n";
    return 0;
}
