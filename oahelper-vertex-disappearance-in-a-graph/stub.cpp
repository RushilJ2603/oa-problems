#include <bits/stdc++.h>
using namespace std;

int solve(int N, vector<int>& A, vector<int>& B) {
    // WRITE YOUR CODE HERE
    return 0;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int N, M;
    if (!(cin >> N >> M)) return 0;
    vector<int> A(M), B(M);
    for (int i = 0; i < M; i++) cin >> A[i];
    for (int i = 0; i < M; i++) cin >> B[i];
    cout << solve(N, A, B) << "\n";
    return 0;
}
