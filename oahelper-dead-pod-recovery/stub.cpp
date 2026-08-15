#include <iostream>
#include <vector>

using namespace std;

vector<int> recoverDeadPods(int pods, const vector<vector<int>>& connections, const vector<vector<int>>& queries) {
    // WRITE YOUR CODE HERE
    return {};
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int pods;
    if (!(cin >> pods)) return 0;
    
    int n, dummy;
    if (!(cin >> n >> dummy)) return 0;
    
    vector<vector<int>> connections(n, vector<int>(2));
    for (int i = 0; i < n; ++i) {
        cin >> connections[i][0] >> connections[i][1];
    }
    
    int q;
    if (!(cin >> q >> dummy)) return 0;
    
    vector<vector<int>> queries(q, vector<int>(2));
    for (int i = 0; i < q; ++i) {
        cin >> queries[i][0] >> queries[i][1];
    }
    
    vector<int> result = recoverDeadPods(pods, connections, queries);
    for (int res : result) {
        cout << res << "\n";
    }
    return 0;
}
