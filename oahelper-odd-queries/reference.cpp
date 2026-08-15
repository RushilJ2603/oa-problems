#include <iostream>
#include <vector>
#include <cstring>

using namespace std;

struct Node {
    unsigned long long words[16]; // 16 * 64 = 1024 bits

    Node() {
        memset(words, 0, sizeof(words));
    }

    void flip(int pos) {
        words[pos >> 6] ^= (1ULL << (pos & 63));
    }

    void xor_with(const Node& other) {
        for (int i = 0; i < 16; ++i) {
            words[i] ^= other.words[i];
        }
    }

    int count() const {
        int cnt = 0;
        for (int i = 0; i < 16; ++i) {
            cnt += __builtin_popcountll(words[i]);
        }
        return cnt;
    }
};

struct FenwickTree {
    int n;
    vector<Node> tree;

    FenwickTree(int n) : n(n), tree(n + 1) {}

    void update(int idx, int val) {
        for (; idx <= n; idx += idx & -idx) {
            tree[idx].flip(val);
        }
    }

    Node query(int idx) {
        Node res;
        for (; idx > 0; idx -= idx & -idx) {
            res.xor_with(tree[idx]);
        }
        return res;
    }

    int query_range(int l, int r) {
        Node res = query(r);
        res.xor_with(query(l - 1));
        return res.count();
    }
};

vector<int> solve(int N, int Q, vector<int>& Arr, const vector<vector<int>>& queries) {
    FenwickTree ft(N);
    for (int i = 1; i <= N; ++i) {
        ft.update(i, Arr[i - 1]);
    }
    
    vector<int> ans;
    for (const auto& q : queries) {
        if (q[0] == 1) {
            int i = q[1];
            int v = q[2];
            ft.update(i, Arr[i - 1]); // remove old value
            Arr[i - 1] = v;
            ft.update(i, Arr[i - 1]); // add new value
        } else {
            int l = q[1];
            int r = q[2];
            ans.push_back(ft.query_range(l, r));
        }
    }
    return ans;
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
