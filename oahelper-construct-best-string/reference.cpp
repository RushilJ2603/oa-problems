#include <bits/stdc++.h>
using namespace std;

long long solve(int n, vector<string>& list, vector<int>& points, int limit) {
    if (n == 0 || limit == 0) return 0;

    int max_nodes = 2;
    for (const string& s : list) max_nodes += (int)s.length();

    vector<vector<int>> trie(max_nodes, vector<int>(26, 0));
    vector<int> fail(max_nodes, 0);
    vector<long long> val(max_nodes, 0);
    int node_count = 1;

    for (int i = 0; i < n; ++i) {
        int u = 0;
        for (char c : list[i]) {
            int idx = c - 'a';
            if (!trie[u][idx]) trie[u][idx] = node_count++;
            u = trie[u][idx];
        }
        val[u] += points[i];
    }

    queue<int> q;
    for (int i = 0; i < 26; ++i)
        if (trie[0][i]) q.push(trie[0][i]);

    while (!q.empty()) {
        int u = q.front();
        q.pop();
        val[u] += val[fail[u]];
        for (int i = 0; i < 26; ++i) {
            if (trie[u][i]) {
                fail[trie[u][i]] = trie[fail[u]][i];
                q.push(trie[u][i]);
            } else {
                trie[u][i] = trie[fail[u]][i];
            }
        }
    }

    long long dp_ops = (long long)limit * node_count * 10;
    long long mat_ops = (long long)node_count * node_count * node_count * 30;

    if (mat_ops < dp_ops) {
        vector<vector<long long>> mat(node_count, vector<long long>(node_count, -1));
        for (int u = 0; u < node_count; ++u) {
            for (int i = 0; i < 26; ++i) {
                int v = trie[u][i];
                if (mat[u][v] < val[v]) mat[u][v] = val[v];
            }
        }
        vector<vector<long long>> res(node_count, vector<long long>(node_count, -1));
        for (int i = 0; i < node_count; ++i) res[i][i] = 0;
        vector<vector<long long>> a = mat;
        long long p = limit;

        auto mul = [&](const vector<vector<long long>>& A, const vector<vector<long long>>& B) {
            vector<vector<long long>> C(node_count, vector<long long>(node_count, -1));
            for (int i = 0; i < node_count; ++i) {
                for (int k = 0; k < node_count; ++k) {
                    if (A[i][k] != -1) {
                        for (int j = 0; j < node_count; ++j) {
                            if (B[k][j] != -1) {
                                if (C[i][j] < A[i][k] + B[k][j])
                                    C[i][j] = A[i][k] + B[k][j];
                            }
                        }
                    }
                }
            }
            return C;
        };

        while (p > 0) {
            if (p % 2 == 1) res = mul(res, a);
            a = mul(a, a);
            p /= 2;
        }
        long long ans = 0;
        for (int i = 0; i < node_count; ++i)
            if (res[0][i] > ans) ans = res[0][i];
        return ans;
    }

    vector<vector<int>> unique_v(node_count);
    for (int u = 0; u < node_count; ++u) {
        vector<int> vs;
        for (int i = 0; i < 26; ++i) vs.push_back(trie[u][i]);
        sort(vs.begin(), vs.end());
        vs.erase(unique(vs.begin(), vs.end()), vs.end());
        unique_v[u] = vs;
    }

    vector<long long> dp(node_count, -1), next_dp(node_count, -1);
    dp[0] = 0;
    long long max_ans = 0;
    for (int L = 1; L <= limit; ++L) {
        fill(next_dp.begin(), next_dp.begin() + node_count, -1);
        for (int u = 0; u < node_count; ++u) {
            if (dp[u] != -1) {
                long long dpu = dp[u];
                for (int v : unique_v[u]) {
                    if (dpu + val[v] > next_dp[v]) next_dp[v] = dpu + val[v];
                }
            }
        }
        swap(dp, next_dp);
        for (int u = 0; u < node_count; ++u)
            if (dp[u] > max_ans) max_ans = dp[u];
    }
    return max_ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    if (!(cin >> n)) return 0;
    vector<string> list(n);
    vector<int> points(n);
    for (int i = 0; i < n; ++i) cin >> list[i];
    for (int i = 0; i < n; ++i) cin >> points[i];
    int limit;
    cin >> limit;
    cout << solve(n, list, points, limit) << "\n";
    return 0;
}
