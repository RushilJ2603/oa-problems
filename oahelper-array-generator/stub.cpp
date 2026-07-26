#include <bits/stdc++.h>
using namespace std;

vector<long long> solve(int n, vector<long long>& values, string state, long long m) {
    // WRITE YOUR CODE HERE
    return {};
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    if (!(cin >> n)) return 0;
    vector<long long> values(n);
    for (int i = 0; i < n; i++) cin >> values[i];
    string state;
    cin >> state;
    long long m;
    cin >> m;
    vector<long long> result = solve(n, values, state, m);
    if (result.empty()) {
        cout << "\n";
    } else {
        for (int i = 0; i < (int)result.size(); i++) {
            if (i) cout << ' ';
            cout << result[i];
        }
        cout << "\n";
    }
    return 0;
}
