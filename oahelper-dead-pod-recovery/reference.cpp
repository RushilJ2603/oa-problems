#include <iostream>
#include <vector>
#include <numeric>

using namespace std;

struct DSU {
    vector<int> parent;
    DSU(int n) {
        parent.resize(n + 1);
        iota(parent.begin(), parent.end(), 0);
    }
    int find(int i) {
        if (parent[i] == i)
            return i;
        return parent[i] = find(parent[i]);
    }
    void unite(int i, int j) {
        int root_i = find(i);
        int root_j = find(j);
        if (root_i != root_j) {
            parent[root_i] = root_j;
        }
    }
};

vector<int> recoverDeadPods(int pods, const vector<vector<int>>& connections, const vector<vector<int>>& queries) {
    DSU dsu(pods);
    for (const auto& conn : connections) {
        dsu.unite(conn[0], conn[1]);
    }

    vector<int> root(pods + 1);
    for (int i = 1; i <= pods; ++i) {
        root[i] = dsu.find(i);
    }

    vector<vector<int>> components(pods + 1);
    for (int i = 1; i <= pods; ++i) {
        components[root[i]].push_back(i);
    }

    vector<int> heads(pods + 1, 0);
    vector<bool> active(pods + 1, true);

    vector<int> result;
    for (const auto& q : queries) {
        int type = q[0];
        int pod_id = q[1];
        if (type == 2) {
            active[pod_id] = false;
        } else if (type == 1) {
            if (active[pod_id]) {
                result.push_back(pod_id);
            } else {
                int r = root[pod_id];
                const auto& comp = components[r];
                int& h = heads[r];
                while (h < comp.size() && !active[comp[h]]) {
                    h++;
                }
                if (h < comp.size()) {
                    result.push_back(comp[h]);
                } else {
                    result.push_back(-1);
                }
            }
        }
    }
    return result;
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
