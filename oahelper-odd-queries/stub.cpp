#include <iostream>
#include <vector>

using namespace std;

vector<int> solve(int N, int Q, vector<int>& Arr, const vector<vector<int>>& queries) {
    // WRITE YOUR CODE HERE
    return {};
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int T;
    if (!(cin >> T)) return 0;
    while (T--) {
        int N, Q;
        cin >> N >> Q;
        vector<int> Arr(N);
        for (int i = 0; i < N; ++i) {
            cin >> Arr[i];
        }
        vector<vector<int>> queries(Q, vector<int>(3));
        for (int i = 0; i < Q; ++i) {
            cin >> queries[i][0] >> queries[i][1] >> queries[i][2];
        }
        vector<int> res = solve(N, Q, Arr, queries);
        for (size_t i = 0; i < res.size(); ++i) {
            cout << res[i] << (i + 1 == res.size() ? "" : " ");
        }
        cout << "\n";
    }
    return 0;
}
