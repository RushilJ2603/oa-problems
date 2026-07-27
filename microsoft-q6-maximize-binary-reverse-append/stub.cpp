#include <bits/stdc++.h>
using namespace std;

// Return a permutation of s that maximizes the final string produced by the
// reverse-and-append procedure.
string solveOne(const string &s) {
    // WRITE YOUR CODE HERE
    return s;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    if (!(cin >> T)) return 0;
    while (T--) {
        string s;
        cin >> s;
        cout << solveOne(s) << "\n";
    }
    return 0;
}
