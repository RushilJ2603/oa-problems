#include <bits/stdc++.h>
using namespace std;

long long solve(int n, vector<int>& board) {
    // WRITE YOUR CODE HERE
    return 0;
}

vector<int> read_board() {
    string raw((istreambuf_iterator<char>(cin)), istreambuf_iterator<char>());
    // Bracketed form: extract every 0/1 character.
    if (raw.find('[') != string::npos) {
        vector<int> board;
        for (char ch : raw) {
            if (ch == '0' || ch == '1') board.push_back(ch - '0');
        }
        return board;
    }
    // Standard form: N then N integers.
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
    int n = (int)board.size();
    cout << solve(n, board) << "\n";
    return 0;
}
