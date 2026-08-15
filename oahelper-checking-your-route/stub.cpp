#include <bits/stdc++.h>
using namespace std;

vector<string> classifyEdges(int g_nodes, vector<int>& g_from, vector<int>& g_to, vector<int>& g_weight) {
    // WRITE YOUR CODE HERE
    return {};
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int g_nodes, g_edges;
    if (!(cin >> g_nodes >> g_edges)) return 0;
    vector<int> g_from(g_edges), g_to(g_edges), g_weight(g_edges);
    for (int i = 0; i < g_edges; i++) {
        cin >> g_from[i] >> g_to[i] >> g_weight[i];
    }
    vector<string> res = classifyEdges(g_nodes, g_from, g_to, g_weight);
    for (const string& s : res) cout << s << "\n";
    return 0;
}
