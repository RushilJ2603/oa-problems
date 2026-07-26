#include <bits/stdc++.h>
using namespace std;

long long solve(int n, vector<int>& parent, vector<int>& values) {
    vector<vector<int>> children(n);
    int root = 0;
    for (int i = 0; i < n; ++i) {
        if (parent[i] == -1) root = i;
        else children[parent[i]].push_back(i);
    }
    vector<long long> dp(n, 0);
    long long ans = LLONG_MIN;
    vector<int> order;
    order.reserve(n);
    stack<int> st;
    st.push(root);
    while (!st.empty()) {
        int u = st.top();
        st.pop();
        order.push_back(u);
        for (int v : children[u]) st.push(v);
    }
    for (int i = (int)order.size() - 1; i >= 0; --i) {
        int u = order[i];
        long long bestChild = 0;
        for (int v : children[u]) bestChild = max(bestChild, dp[v]);
        dp[u] = (long long)values[u] + max(0LL, bestChild);
        ans = max(ans, dp[u]);
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    if (!(cin >> n)) return 0;
    vector<int> parent(n), values(n);
    for (int i = 0; i < n; ++i) cin >> parent[i];
    for (int i = 0; i < n; ++i) cin >> values[i];
    cout << solve(n, parent, values) << "\n";
    return 0;
}
