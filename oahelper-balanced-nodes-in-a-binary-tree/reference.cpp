#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct Node {
    long long val = 0;
    Node* left = nullptr;
    Node* right = nullptr;
};

pair<long long, long long> dfs(Node* node) {
    if (!node) return {0, 0};
    auto l = dfs(node->left);
    auto r = dfs(node->right);
    long long subtreeSum = node->val + l.first + r.first;
    long long balancedSum = l.second + r.second;
    if (node->left && node->right) {
        if ((l.first & 1LL) != (r.first & 1LL)) {
            balancedSum += node->val;
        }
    }
    return {subtreeSum, balancedSum};
}

long long solve(int n, long long root_val, const vector<pair<string, long long>>& edges) {
    Node* root = new Node();
    root->val = root_val;
    for (const auto& edge : edges) {
        Node* cur = root;
        for (char c : edge.first) {
            if (c == 'L') {
                if (!cur->left) cur->left = new Node();
                cur = cur->left;
            } else {
                if (!cur->right) cur->right = new Node();
                cur = cur->right;
            }
        }
        cur->val = edge.second;
    }
    return dfs(root).second;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    if (cin >> n) {
        long long root_val;
        cin >> root_val;
        vector<pair<string, long long>> edges(n - 1);
        for (int i = 0; i < n - 1; ++i) {
            cin >> edges[i].first >> edges[i].second;
        }
        cout << solve(n, root_val, edges) << "\n";
    }
    return 0;
}
