#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const long long INF = 4e18; // Sufficiently large value for min comparisons

struct Break {
    long long l, r;
    long long cap;
    long long S, E; // Slot indices range [S, E]
    long long val;  // Value for RMQ: l + t - S * t
    long long k_start; // Value for start calculation: r - (cap + S) * t
};

// Segment Tree for Range Minimum Query
struct SegTree {
    int size;
    vector<long long> tree;

    SegTree(int n, const vector<long long>& data) {
        size = n;
        tree.resize(4 * n, INF);
        build(data, 1, 0, n - 1);
    }

    void build(const vector<long long>& data, int v, int tl, int tr) {
        if (tl == tr) {
            tree[v] = data[tl];
        } else {
            int tm = (tl + tr) / 2;
            build(data, 2 * v, tl, tm);
            build(data, 2 * v + 1, tm + 1, tr);
            tree[v] = min(tree[2 * v], tree[2 * v + 1]);
        }
    }

    long long query(int v, int tl, int tr, int l, int r) {
        if (l > r) return INF;
        if (l == tl && r == tr) return tree[v];
        int tm = (tl + tr) / 2;
        return min(query(2 * v, tl, tm, l, min(r, tm)),
                   query(2 * v + 1, tm + 1, tr, max(l, tm + 1), r));
    }

    long long query(int l, int r) {
        return query(1, 0, size - 1, l, r);
    }
};

void solve() {
    int n;
    long long m, t, k;
    if (!(cin >> n >> m >> t >> k)) return;

    vector<pair<long long, long long>> raw_breaks(n);
    for (int i = 0; i < n; ++i) {
        cin >> raw_breaks[i].first >> raw_breaks[i].second;
    }

    vector<Break> breaks;
    breaks.reserve(n);
    
    long long current_S = 0;
    vector<long long> E_list;
    vector<long long> S_list;
    vector<long long> vals;

    // Filter valid breaks and compute properties
    for (int i = 0; i < n; ++i) {
        long long l = raw_breaks[i].first;
        long long r = raw_breaks[i].second;
        // Capacity is floor((r - l) / t)
        if (r < l) continue; 
        long long cap = (r - l) / t;
        
        if (cap > 0) {
            Break b;
            b.l = l;
            b.r = r;
            b.cap = cap;
            b.S = current_S;
            b.E = current_S + cap - 1;
            
            // Val_j = l + t - S * t
            b.val = l + t - b.S * t;
            
            // K_start = r - (cap + S) * t
            b.k_start = r - (b.cap + b.S) * t;
            
            breaks.push_back(b);
            E_list.push_back(b.E);
            S_list.push_back(b.S);
            vals.push_back(b.val);
            
            current_S += cap;
        }
    }
    
    long long C = current_S;
    if (C == 0) {
        cout << -1 << "\n";
        return;
    }
    
    int active_n = breaks.size();
    SegTree st(active_n, vals);
    
    long long min_minutes = INF;
    long long rem = (m - 1) % C;
    long long base_days = (m - 1) / C;
    
    // Iterate over every break as a potential starting break
    for (int i = 0; i < active_n; ++i) {
        long long Si = breaks[i].S;
        long long Ei = breaks[i].E;
        long long k_start = breaks[i].k_start;
        
        // We split the range of slots in break i into two parts:
        // Part 1: Slots u where (u + rem) does not wrap around the total capacity C.
        // Condition: u + rem < C  =>  u < C - rem
        long long limit = C - rem - 1;
        long long R1 = min(Ei, limit);
        
        if (Si <= R1) {
            long long v_start = Si + rem;
            long long v_end = R1 + rem;
            
            // Find breaks that overlap with [v_start, v_end]
            auto it_start = lower_bound(E_list.begin(), E_list.end(), v_start);
            int idx_start = distance(E_list.begin(), it_start);
            
            auto it_end = upper_bound(S_list.begin(), S_list.end(), v_end);
            int idx_end = distance(S_list.begin(), it_end) - 1;
            
            if (idx_start <= idx_end) {
                long long min_val = st.query(idx_start, idx_end);
                long long current_cost = min_val - k_start + rem * t + base_days * k;
                if (current_cost < min_minutes) min_minutes = current_cost;
            }
        }
        
        // Part 2: Slots u where (u + rem) wraps around C.
        // Condition: u >= C - rem
        long long L2 = max(Si, C - rem);
        if (L2 <= Ei) {
            long long v_start = L2 + rem - C;
            long long v_end = Ei + rem - C;
            
            auto it_start = lower_bound(E_list.begin(), E_list.end(), v_start);
            int idx_start = distance(E_list.begin(), it_start);
            
            auto it_end = upper_bound(S_list.begin(), S_list.end(), v_end);
            int idx_end = distance(S_list.begin(), it_end) - 1;
            
            if (idx_start <= idx_end) {
                long long min_val = st.query(idx_start, idx_end);
                long long current_cost = min_val - k_start + (rem - C) * t + (base_days + 1) * k;
                if (current_cost < min_minutes) min_minutes = current_cost;
            }
        }
    }
    
    if (min_minutes >= INF) cout << -1 << "\n";
    else cout << min_minutes << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    if (cin >> t) {
        while (t--) {
            solve();
        }
    }
    return 0;
}