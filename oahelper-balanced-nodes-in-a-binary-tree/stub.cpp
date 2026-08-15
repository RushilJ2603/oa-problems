#include <iostream>
#include <string>
#include <vector>
#include <map>

using namespace std;

long long solve(int n, long long root_val, const vector<pair<string, long long>>& edges) {
    // WRITE YOUR CODE HERE
    return 0;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    if (cin >> n) {
        long long root_val;
        cin >> root_val;
        vector<pair<string, long long>> edges(n - 1);
        for (int i = 0; i < n - 1; ++i) {
            cin >> edges[i].first >> edges[i].second;
        }
        cout << solve(n, root_val, edges) << "\n";
    }
    return 0;
}
