#include <bits/stdc++.h>
using namespace std;

class DSU {
public:
    vector<int> parent;
    DSU(int n) {
        parent.resize(n + 1);
        iota(parent.begin(), parent.end(), 0);
    }
    int find(int x) {
        if (parent[x] == x) return x;
        return parent[x] = find(parent[x]);
    }
    void unite(int a, int b) {
        a = find(a);
        b = find(b);
        if (a != b) parent[b] = a;
    }
};

vector<int> getAssignedCluster(int clusters, int m, vector<vector<int>>& connections, int q, vector<vector<int>>& queries) {
    DSU dsu(clusters);
    for (auto& edge : connections) {
        dsu.unite(edge[0], edge[1]);
    }
    
    unordered_map<int, vector<int>> comp;
    for (int i = 1; i <= clusters; i++) {
        comp[dsu.find(i)].push_back(i);
    }
    
    vector<int> compId(clusters + 1);
    vector<priority_queue<int, vector<int>, greater<int>>> heaps;
    int idx = 0;
    for (auto& kv : comp) {
        priority_queue<int, vector<int>, greater<int>> pq;
        for (int node : kv.second) {
            pq.push(node);
            compId[node] = idx;
        }
        heaps.push_back(move(pq));
        idx++;
    }
    
    vector<bool> active(clusters + 1, true);
    vector<int> answer;
    
    for (auto& query : queries) {
        int type = query[0];
        int clusterId = query[1];
        if (type == 2) {
            active[clusterId] = false;
        } else {
            int c = compId[clusterId];
            while (!heaps[c].empty() && !active[heaps[c].top()]) {
                heaps[c].pop();
            }
            if (heaps[c].empty()) {
                answer.push_back(-1);
            } else {
                answer.push_back(heaps[c].top());
            }
        }
    }
    return answer;
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
