#include <bits/stdc++.h>
using namespace std;

vector<int> solve(int n, vector<int>& signature) {
    // WRITE YOUR CODE HERE
    return vector<int>(n, 0);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    if (!(cin >> n)) return 0;
    vector<int> signature(n);
    for (int i = 0; i < n; i++) cin >> signature[i];
    vector<int> ans = solve(n, signature);
    for (int x : ans) cout << x << "\n";
    return 0;
}
