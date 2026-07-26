#include <bits/stdc++.h>
using namespace std;

long long solve(int n, vector<long long>& A, vector<long long>& B) {
    // WRITE YOUR CODE HERE
    return 0;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    if (!(cin >> n)) return 0;
    vector<long long> A(n), B(n);
    for (int i = 0; i < n; i++) cin >> A[i];
    for (int i = 0; i < n; i++) cin >> B[i];
    cout << solve(n, A, B) << "\n";
    return 0;
}
