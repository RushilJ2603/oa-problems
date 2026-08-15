#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>

using namespace std;

vector<int> palindromePaths(int tree_nodes, const vector<int>& tree_from, const vector<int>& tree_to, const vector<char>& arr, const vector<int>& queries) {
    vector<vector<int>> adj(tree_nodes);
    for (int i = 0; i < tree_nodes - 1; ++i) {
        adj[tree_from[i]].push_back(tree_to[i]);
        adj[tree_to[i]].push_back(tree_from[i]);
    }
    
    vector<int> node_ans(tree_nodes, 0);
    unordered_map<int, int> freq;
    
    freq[0] = 1; // Base case for the root's path (parent of root has mask 0)
    
    // We can use a recursive lambda
    auto dfs = [&](auto& self, int u, int p, int current_mask) -> void {
        int char_bit = 1 << (arr[u] - 'a');
        int node_mask = current_mask ^ char_bit;
        
        int count = freq[node_mask];
        for (int i = 0; i < 26; ++i) {
            count += freq[node_mask ^ (1 << i)];
        }
        node_ans[u] = count;
        
        freq[node_mask]++;
        for (int v : adj[u]) {
            if (v != p) {
                self(self, v, u, node_mask);
            }
        }
        freq[node_mask]--;
    };
    
    dfs(dfs, 0, -1, 0);
    
    vector<int> res(queries.size());
    for (size_t i = 0; i < queries.size(); ++i) {
        res[i] = node_ans[queries[i]];
    }
    return res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n, e;
    if (!(cin >> n >> e)) return 0;
    vector<int> from(e), to(e);
    for (int i = 0; i < e; ++i) {
        cin >> from[i] >> to[i];
    }
    int c;
    cin >> c;
    vector<char> arr(c);
    for (int i = 0; i < c; ++i) {
        cin >> arr[i];
    }
    int m;
    cin >> m;
    vector<int> queries(m);
    for (int i = 0; i < m; ++i) {
        cin >> queries[i];
    }
    vector<int> res = palindromePaths(n, from, to, arr, queries);
    for (int x : res) {
        cout << x << "\n";
    }
    return 0;
}
