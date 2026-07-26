#include <bits/stdc++.h>
using namespace std;

// Returns final balances, or a single-element vector {-k} on first invalid request.
vector<long long> solve(int n, vector<long long> bal,
                        const vector<tuple<string, long long, int, long long>>& reqs) {
    // WRITE YOUR CODE HERE
    return {};
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    if (!(cin >> n)) return 0;
    vector<long long> bal(n);
    for (int i = 0; i < n; i++) cin >> bal[i];
    int m;
    cin >> m;
    vector<tuple<string, long long, int, long long>> reqs(m);
    for (int i = 0; i < m; i++) {
        string op;
        long long ts, amt;
        int h;
        cin >> op >> ts >> h >> amt;
        reqs[i] = {op, ts, h, amt};
    }
    auto ans = solve(n, bal, reqs);
    for (size_t i = 0; i < ans.size(); i++) {
        if (i) cout << ' ';
        cout << ans[i];
    }
    cout << '\n';
    return 0;
}
