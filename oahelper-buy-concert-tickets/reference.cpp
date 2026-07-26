#include <bits/stdc++.h>
using namespace std;

struct Node {
    long long cost;
    long long step;
    bool operator>(const Node& other) const {
        if (cost != other.cost) return cost > other.cost;
        return step > other.step;
    }
};

long long solve(long long m, long long k) {
    if (m == 0) return 0;
    if (k == 1) return m;

    long long limit = 2 * m - 1;
    priority_queue<Node, vector<Node>, greater<Node>> pq;

    long long p = 1;
    while (true) {
        pq.push({p, 2 * p});
        if (p > limit / k) break;
        p *= k;
    }

    long long ans = 0;
    for (long long i = 0; i < m; ++i) {
        Node cur = pq.top();
        pq.pop();
        ans += cur.cost;
        cur.cost += cur.step;
        pq.push(cur);
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    long long m, k;
    if (!(cin >> m >> k)) return 0;
    cout << solve(m, k) << "\n";
    return 0;
}
