#include <iostream>
#include <vector>
#include <string>

using namespace std;

vector<int> palindromePaths(int tree_nodes, const vector<int>& tree_from, const vector<int>& tree_to, const vector<char>& arr, const vector<int>& queries) {
    // WRITE YOUR CODE HERE
    return {};
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n, e;
    if (!(cin >> n >> e)) return 0;
    vector<int> from(e), to(e);
    for (int i = 0; i < e; ++i) {
        cin >> from[i] >> to[i];
    }
    int c;
    cin >> c;
    vector<char> arr(c);
    for (int i = 0; i < c; ++i) {
        cin >> arr[i];
    }
    int m;
    cin >> m;
    vector<int> queries(m);
    for (int i = 0; i < m; ++i) {
        cin >> queries[i];
    }
    vector<int> res = palindromePaths(n, from, to, arr, queries);
    for (int x : res) {
        cout << x << "\n";
    }
    return 0;
}
