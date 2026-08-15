#include <bits/stdc++.h>
using namespace std;

vector<int> getAssignedCluster(int clusters, int m, vector<vector<int>>& connections, int q, vector<vector<int>>& queries) {
    // WRITE YOUR CODE HERE
    return {};
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int clusters, m;
    if (!(cin >> clusters >> m)) return 0;
    vector<vector<int>> connections(m, vector<int>(2));
    for (int i = 0; i < m; i++) {
        cin >> connections[i][0] >> connections[i][1];
    }
    int q;
    cin >> q;
    vector<vector<int>> queries(q, vector<int>(2));
    for (int i = 0; i < q; i++) {
        cin >> queries[i][0] >> queries[i][1];
    }
    vector<int> result = getAssignedCluster(clusters, m, connections, q, queries);
    for (int i = 0; i < result.size(); i++) {
        cout << result[i] << "\n";
    }
    return 0;
}
