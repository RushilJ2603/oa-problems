#include <bits/stdc++.h>
using namespace std;

// Return the answer for every query, in order.
vector<long long> solve(int n, const vector<int> &treeFrom, const vector<int> &treeTo,
                        const string &letters, const vector<int> &queries) {
    // WRITE YOUR CODE HERE
    return vector<long long>(queries.size(), 0);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<int> treeFrom(max(0, n - 1)), treeTo(max(0, n - 1));
    for (int i = 0; i + 1 < n; i++) cin >> treeFrom[i];
    for (int i = 0; i + 1 < n; i++) cin >> treeTo[i];
    string letters;
    cin >> letters;
    int q;
    cin >> q;
    vector<int> queries(q);
    for (int i = 0; i < q; i++) cin >> queries[i];
    string out;
    for (long long v : solve(n, treeFrom, treeTo, letters, queries)) {
        out += to_string(v);
        out += '\n';
    }
    cout << out;
    return 0;
}
