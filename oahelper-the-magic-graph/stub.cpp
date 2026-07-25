#include <bits/stdc++.h>
using namespace std;

int solve(int N, int M, vector<int>& L, vector<int>& R, vector<int>& C) {
    // WRITE YOUR CODE HERE
    return 0;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int N, M;
    if (!(cin >> N >> M)) return 0;
    vector<int> L(M), R(M), C(M);
    for (int i = 0; i < M; i++) cin >> L[i];
    for (int i = 0; i < M; i++) cin >> R[i];
    for (int i = 0; i < M; i++) cin >> C[i];
    cout << solve(N, M, L, R, C) << "\n";
    return 0;
}
