#include <bits/stdc++.h>
using namespace std;

const int MOD = 1000000007;

using Mat = vector<vector<int>>;

Mat mul(const Mat& A, const Mat& B) {
    int n = (int)A.size();
    Mat C(n, vector<int>(n, 0));
    for (int i = 0; i < n; i++) {
        for (int t = 0; t < n; t++) {
            if (!A[i][t]) continue;
            long long ait = A[i][t];
            for (int j = 0; j < n; j++) {
                C[i][j] = (int)((C[i][j] + ait * B[t][j]) % MOD);
            }
        }
    }
    return C;
}

Mat mpow(Mat A, long long p) {
    int n = (int)A.size();
    Mat R(n, vector<int>(n, 0));
    for (int i = 0; i < n; i++) R[i][i] = 1;
    while (p > 0) {
        if (p & 1) R = mul(R, A);
        A = mul(A, A);
        p >>= 1;
    }
    return R;
}

long long solve(int n, long long k, const vector<pair<int,int>>& edges) {
    Mat A(n, vector<int>(n, 0));
    for (auto [u, v] : edges) {
        A[u - 1][v - 1]++;
        if (A[u - 1][v - 1] >= MOD) A[u - 1][v - 1] -= MOD;
    }
    Mat R = mpow(A, k);
    return R[0][n - 1];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    long long k;
    if (!(cin >> n >> m >> k)) return 0;
    vector<pair<int,int>> edges(m);
    for (int i = 0; i < m; i++) cin >> edges[i].first >> edges[i].second;
    cout << solve(n, k, edges) << "\n";
    return 0;
}
