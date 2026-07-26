#include <bits/stdc++.h>
using namespace std;

// knows[i][j] == 1 iff person i knows person j (knows[i][i] == 0). Return the index of the celebrity
// (known by everyone else, knows no one), or -1 if there is none.
int celebrity(int n, vector<vector<int>>& knows) {
    // WRITE YOUR CODE HERE
    return -1;
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
