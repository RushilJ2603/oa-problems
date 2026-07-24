#include <bits/stdc++.h>
using namespace std;

// Play the given key presses on the initial 4x4 board and return the CUMULATIVE
// score after each press. grid is the starting board; moves[k] is "U"/"D"/"L"/"R".
vector<long long> play(vector<vector<long long>>& grid, const vector<string>& moves) {
    vector<long long> scores;
    // WRITE YOUR CODE HERE
    return scores;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    vector<vector<long long>> grid(4, vector<long long>(4));
    for (auto& row : grid)
        for (auto& x : row) cin >> x;
    int n;
    cin >> n;
    vector<string> moves(n);
    for (auto& mv : moves) cin >> mv;

    string out;
    for (long long s : play(grid, moves)) { out += to_string(s); out += "\n"; }
    cout << out;
    return 0;
}
