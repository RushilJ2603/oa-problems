#include <bits/stdc++.h>
using namespace std;

long long solve(int n, vector<int>& board) {
    long long pieces = 0;
    for (int v : board) if (v == 1) ++pieces;
    if (pieces == 0 || pieces == n) return 0;

    // Distance if pieces pack into positions 0..k-1 (order preserved).
    long long left_dist = 0;
    long long seen = 0;
    for (int i = 0; i < n; ++i) {
        if (board[i] == 1) {
            left_dist += i - seen;
            ++seen;
        }
    }
    // Each piece-empty pair is crossed by exactly one of the two extreme packings.
    long long total_pairs = pieces * (n - pieces);
    long long right_dist = total_pairs - left_dist;
    return max(left_dist, right_dist);
}

vector<int> read_board() {
    string raw((istreambuf_iterator<char>(cin)), istreambuf_iterator<char>());
    if (raw.find('[') != string::npos) {
        vector<int> board;
        for (char ch : raw) {
            if (ch == '0' || ch == '1') board.push_back(ch - '0');
        }
        return board;
    }
    stringstream ss(raw);
    int n;
    if (!(ss >> n)) return {};
    vector<int> board(n);
    for (int i = 0; i < n; ++i) ss >> board[i];
    return board;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    vector<int> board = read_board();
    cout << solve((int)board.size(), board) << "\n";
    return 0;
}
