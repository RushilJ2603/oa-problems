#include <iostream>
#include <vector>

using namespace std;

int solve(int n, int m, const vector<vector<int>>& edges) {
    vector<int> incoming_masks(n, 0);
    for (const auto& edge : edges) {
        int u = edge[0] - 1;
        int v = edge[1] - 1;
        incoming_masks[v] |= (1 << u);
    }
    
    int total_masks = 1 << n;
    vector<bool> dp(total_masks, false);
    dp[0] = true;
    int max_nodes = 0;
    
    for (int mask = 0; mask < total_masks; ++mask) {
        if (!dp[mask]) continue;
        int set_bits = __builtin_popcount(mask);
        if (set_bits > max_nodes) {
            max_nodes = set_bits;
        }
        for (int i = 0; i < n; ++i) {
            if (!((mask >> i) & 1)) {
                int next_mask = mask | (1 << i);
                if (!(incoming_masks[i] & next_mask)) {
                    dp[next_mask] = true;
                }
            }
        }
    }
    return max_nodes;
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
