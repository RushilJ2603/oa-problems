#include <bits/stdc++.h>
using namespace std;

vector<int> solve(int n, vector<long long>& priorities) {
    // WRITE YOUR CODE HERE
    return vector<int>(n, 0);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    if (!(cin >> n)) return 0;
    vector<long long> priorities(n);
    for (int i = 0; i < n; i++) {
        cin >> priorities[i];
    }
    vector<int> ans = solve(n, priorities);
    for (int i = 0; i < n; i++) {
        cout << ans[i] << (i == n - 1 ? "" : " ");
    }
    cout << "\n";
    return 0;
}
