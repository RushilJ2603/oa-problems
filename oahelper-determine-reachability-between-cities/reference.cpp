#include <bits/stdc++.h>
using namespace std;

struct TrainLine {
    string lineName;
    vector<string> stations;
};

class UnionFind {
public:
    vector<int> parent, rank_;
    UnionFind(int n) : parent(n), rank_(n, 0) {
        for (int i = 0; i < n; i++) parent[i] = i;
    }
    int find(int x) {
        if (parent[x] != x) parent[x] = find(parent[x]);
        return parent[x];
    }
    void unite(int a, int b) {
        a = find(a);
        b = find(b);
        if (a != b) {
            if (rank_[a] < rank_[b]) swap(a, b);
            parent[b] = a;
            if (rank_[a] == rank_[b]) rank_[a]++;
        }
    }
};

vector<bool> canTravel(vector<TrainLine>& trainLines, vector<vector<string>>& queries) {
    unordered_map<string, int> idMap;
    int nextId = 0;
    for (auto& line : trainLines) {
        for (auto& station : line.stations) {
            if (idMap.find(station) == idMap.end()) {
                idMap[station] = nextId++;
            }
        }
    }

    UnionFind uf(nextId);
    for (auto& line : trainLines) {
        if (line.stations.empty()) continue;
        int firstId = idMap[line.stations[0]];
        for (size_t i = 1; i < line.stations.size(); i++) {
            uf.unite(firstId, idMap[line.stations[i]]);
        }
    }

    vector<bool> results;
    results.reserve(queries.size());
    for (auto& q : queries) {
        if (q.size() < 2) {
            results.push_back(false);
            continue;
        }
        const string& src = q[0];
        const string& dst = q[1];
        if (src == dst) {
            results.push_back(true);
            continue;
        }
        auto srcIt = idMap.find(src);
        auto dstIt = idMap.find(dst);
        if (srcIt == idMap.end() || dstIt == idMap.end()) {
            results.push_back(false);
            continue;
        }
        results.push_back(uf.find(srcIt->second) == uf.find(dstIt->second));
    }
    return results;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int numLines;
    if (!(cin >> numLines)) return 0;
    vector<TrainLine> trainLines(numLines);
    for (int i = 0; i < numLines; i++) {
        cin >> trainLines[i].lineName;
        int numStations;
        cin >> numStations;
        trainLines[i].stations.resize(numStations);
        for (int j = 0; j < numStations; j++) {
            cin >> trainLines[i].stations[j];
        }
    }
    int numQueries;
    if (!(cin >> numQueries)) return 0;
    vector<vector<string>> queries(numQueries, vector<string>(2));
    for (int i = 0; i < numQueries; i++) {
        cin >> queries[i][0] >> queries[i][1];
    }
    vector<bool> results = canTravel(trainLines, queries);
    for (size_t i = 0; i < results.size(); i++) {
        cout << (results[i] ? "true" : "false");
        if (i + 1 < results.size()) cout << " ";
    }
    cout << "\n";
    return 0;
}
