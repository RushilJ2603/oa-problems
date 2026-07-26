#include <bits/stdc++.h>
using namespace std;

// Return the minimum total cost to travel from (0,0) to (m-1,n-1).
// grid[i][j] is one of 'U','D','L','R' giving the free move from that cell.
int minCost(int m, int n, vector<string>& grid) {
    // WRITE YOUR CODE HERE
    return 0;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int m, n;
    if (!(cin >> m >> n)) return 0;
    vector<string> grid(m);
    for (auto& s : grid) cin >> s;
    cout << minCost(m, n, grid) << "\n";
    return 0;
}
