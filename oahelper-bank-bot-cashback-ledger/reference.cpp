#include <bits/stdc++.h>
using namespace std;

vector<long long> solve(int n, vector<long long> bal,
                        const vector<tuple<string, long long, int, long long>>& reqs) {
    // min-heap of (due_time, holder_index, cashback_amount)
    priority_queue<tuple<long long, int, long long>,
                   vector<tuple<long long, int, long long>>,
                   greater<tuple<long long, int, long long>>> pending;

    for (int i = 0; i < (int)reqs.size(); i++) {
        auto [op, ts, h, amt] = reqs[i];
        while (!pending.empty() && get<0>(pending.top()) <= ts) {
            auto [t, j, a] = pending.top();
            pending.pop();
            bal[j] += a;
        }
        if (h < 1 || h > n) return {-(long long)(i + 1)};
        int j = h - 1;
        if (op == "deposit") {
            bal[j] += amt;
        } else {
            if (amt > bal[j]) return {-(long long)(i + 1)};
            bal[j] -= amt;
            pending.emplace(ts + 86400LL, j, (amt * 2) / 100);
        }
    }
    // Remaining cashbacks are due after the final timestamp — ignore them.
    return bal;
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
