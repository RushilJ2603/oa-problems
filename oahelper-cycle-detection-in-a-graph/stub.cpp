#include <iostream>
#include <vector>

using namespace std;

int solve(int n, int m, const vector<vector<int>>& edges) {
    // WRITE YOUR CODE HERE
    return 0;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n, m;
    if (!(cin >> n >> m)) return 0;
    vector<vector<int>> edges(m, vector<int>(2));
    for (int i = 0; i < m; ++i) {
        cin >> edges[i][0] >> edges[i][1];
    }
    cout << solve(n, m, edges) << "\n";
    return 0;
}
