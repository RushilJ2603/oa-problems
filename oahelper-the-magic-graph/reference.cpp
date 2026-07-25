#include <bits/stdc++.h>
using namespace std;

struct SegTree {
    int n;
    vector<int> tree, lazy;
    SegTree(int n) : n(n), tree(4 * n + 4, 0), lazy(4 * n + 4, 0) {}
    void push(int node) {
        if (lazy[node]) {
            tree[2 * node] += lazy[node];
            lazy[2 * node] += lazy[node];
            tree[2 * node + 1] += lazy[node];
            lazy[2 * node + 1] += lazy[node];
            lazy[node] = 0;
        }
    }
    void update(int node, int start, int end, int l, int r, int val) {
        if (r < start || end < l) return;
        if (l <= start && end <= r) {
            tree[node] += val;
            lazy[node] += val;
            return;
        }
        push(node);
        int mid = (start + end) / 2;
        update(2 * node, start, mid, l, r, val);
        update(2 * node + 1, mid + 1, end, l, r, val);
        tree[node] = min(tree[2 * node], tree[2 * node + 1]);
    }
    void update(int l, int r, int val) {
        if (l > r) return;
        update(1, 1, n, l, r, val);
    }
    int get_min() { return tree[1]; }
};

int solve(int N, int M, vector<int>& L, vector<int>& R, vector<int>& C) {
    if (N <= 1) return 0;
    vector<tuple<int, int, int>> intervals;
    for (int i = 0; i < M; i++) {
        int u = L[i], v = R[i];
        if (u > v) swap(u, v);
        if (u < v) intervals.emplace_back(C[i], u, v - 1);
    }
    if (intervals.empty()) return 0;
    sort(intervals.begin(), intervals.end());
    SegTree st(N - 1);
    int left = 0;
    int ans = INT_MAX;
    int num = (int)intervals.size();
    for (int right = 0; right < num; right++) {
        auto [c, l, r] = intervals[right];
        st.update(l, r, 1);
        while (st.get_min() > 0) {
            ans = min(ans, get<0>(intervals[right]) - get<0>(intervals[left]));
            auto [cl, ll, rr] = intervals[left];
            st.update(ll, rr, -1);
            left++;
        }
    }
    return ans == INT_MAX ? 0 : ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int N, M;
    if (!(cin >> N >> M)) return 0;
    vector<int> L(M), R(M), C(M);
    for (int i = 0; i < M; i++) cin >> L[i];
    for (int i = 0; i < M; i++) cin >> R[i];
    for (int i = 0; i < M; i++) cin >> C[i];
    cout << solve(N, M, L, R, C) << "\n";
    return 0;
}
