#include <bits/stdc++.h>
using namespace std;

using ll = long long;

struct Event {
    int type;  // 0 = BOOK, 1 = QUERY
    int l, r;
    ll p;
};

struct SegmentTree {
    int n;
    vector<ll> mn, mx, lazy;

    SegmentTree(int n) : n(n), mn(4 * n + 5, 0), mx(4 * n + 5, 0), lazy(4 * n + 5, 0) {}

    void apply(int node, ll val) {
        mn[node] += val;
        mx[node] += val;
        lazy[node] += val;
    }

    void push(int node) {
        if (lazy[node] != 0) {
            apply(node << 1, lazy[node]);
            apply(node << 1 | 1, lazy[node]);
            lazy[node] = 0;
        }
    }

    void pull(int node) {
        mn[node] = min(mn[node << 1], mn[node << 1 | 1]);
        mx[node] = max(mx[node << 1], mx[node << 1 | 1]);
    }

    void update(int node, int l, int r, int ql, int qr, ll val) {
        if (ql <= l && r <= qr) {
            apply(node, val);
            return;
        }
        push(node);
        int mid = (l + r) >> 1;
        if (ql <= mid) update(node << 1, l, mid, ql, qr, val);
        if (qr > mid) update(node << 1 | 1, mid + 1, r, ql, qr, val);
        pull(node);
    }

    ll queryMin(int node, int l, int r, int ql, int qr) {
        if (ql <= l && r <= qr) return mn[node];
        push(node);
        int mid = (l + r) >> 1;
        ll res = LLONG_MAX;
        if (ql <= mid) res = min(res, queryMin(node << 1, l, mid, ql, qr));
        if (qr > mid) res = min(res, queryMin(node << 1 | 1, mid + 1, r, ql, qr));
        return res;
    }

    ll globalMax() const { return mx[1]; }
};

vector<ll> solve(int M, int N, ll T, const vector<Event>& events) {
    vector<int> coords;
    coords.reserve(2LL * N + 2);
    coords.push_back(1);
    coords.push_back(M + 1);
    for (const auto& e : events) {
        coords.push_back(e.l);
        coords.push_back(e.r + 1);
    }
    sort(coords.begin(), coords.end());
    coords.erase(unique(coords.begin(), coords.end()), coords.end());

    auto compress = [&](int x) {
        return (int)(lower_bound(coords.begin(), coords.end(), x) - coords.begin());
    };

    vector<Event> ev = events;
    for (auto& e : ev) {
        int origL = e.l, origR = e.r;
        e.l = compress(origL);
        e.r = compress(origR + 1) - 1;
    }

    int blocks = (int)coords.size() - 1;
    SegmentTree st(blocks);

    vector<ll> answers;
    answers.reserve(N);
    int thresholdEvent = -1;

    for (int i = 0; i < N; ++i) {
        const auto& e = ev[i];
        if (e.type == 0) {
            st.update(1, 0, blocks - 1, e.l, e.r, e.p);
            if (thresholdEvent == -1 && st.globalMax() >= T) thresholdEvent = i + 1;
        } else {
            answers.push_back(st.queryMin(1, 0, blocks - 1, e.l, e.r));
        }
    }
    answers.push_back(thresholdEvent);
    return answers;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string raw((istreambuf_iterator<char>(cin)), istreambuf_iterator<char>());
    string normalized;
    normalized.reserve(raw.size());
    for (size_t i = 0; i < raw.size(); ++i) {
        if (raw[i] == '\\' && i + 1 < raw.size() && raw[i + 1] == 'n') {
            normalized.push_back('\n');
            ++i;
        } else {
            normalized.push_back(raw[i]);
        }
    }

    stringstream ss(normalized);
    int M, N;
    ll T;
    if (!(ss >> M >> N >> T)) return 0;

    vector<Event> events;
    events.reserve(N);
    for (int i = 0; i < N; ++i) {
        string op;
        ss >> op;
        if (op == "BOOK") {
            int l, r;
            ll p;
            ss >> l >> r >> p;
            events.push_back({0, l, r, p});
        } else {
            int l, r;
            ss >> l >> r;
            events.push_back({1, l, r, 0});
        }
    }

    vector<ll> ans = solve(M, N, T, events);
    for (ll x : ans) cout << x << '\n';
    return 0;
}
