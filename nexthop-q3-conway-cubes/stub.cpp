#include <bits/stdc++.h>
using namespace std;

long long conwayCubes(int T, const vector<string> &slice) {
    // WRITE YOUR CODE HERE
    return 0;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int R, T;
    if (!(cin >> R >> T)) return 0;
    vector<string> slice;
    for (int i = 0; i < R; i++) {
        string row;
        cin >> row;
        slice.push_back(row);
    }
    cout << conwayCubes(T, slice) << "\n";
    return 0;
}
