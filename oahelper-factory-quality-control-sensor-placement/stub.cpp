#include <bits/stdc++.h>
using namespace std;

long long solve(int N, long long K, vector<long long>& A) {
    // WRITE YOUR CODE HERE
    return 0;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int N;
    long long K;
    if (!(cin >> N >> K)) return 0;
    vector<long long> A(N);
    for (int i = 0; i < N; ++i) cin >> A[i];
    cout << solve(N, K, A) << "\n";
    return 0;
}
