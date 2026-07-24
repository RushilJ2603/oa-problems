#include <bits/stdc++.h>
using namespace std;

// Max score reaching cell n-1 moving +1 or +p (p prime ending in 3) each step.
long long maxGameScore(vector<long long>& cell) {
    // WRITE YOUR CODE HERE
    return 0;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    if (!(cin >> n)) return 0;
    vector<long long> cell(n);
    for (auto& x : cell) cin >> x;
    cout << maxGameScore(cell) << "\n";
    return 0;
}
